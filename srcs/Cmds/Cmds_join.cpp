#include "Server.hpp"



const std::string Server::ListConnectedUsers(std::string const Channel)
{
	
	// find the channel and retrieve the map of connected fd
	std::map<int, std::string> channelFDsMode = this->_channels[Channel]->getChannelFDsModeMap();
	std::map<int, std::string>::iterator it(channelFDsMode.begin());

	// will contain the list of user connected (without the banned users)
	std::string result;
	for ( ; it != channelFDsMode.end() ; it++)
	{   
		// check mode, pos 0 mode, pos 1 @
		std::string combo = it->second;
		if (combo.substr(1,1) == "@")
		{
			result += "@";
		}
		else
		{
			result += " ";
		}
		// get the nick name
		std::map<int, std::string>::iterator it_FD(_fd_nick_list.find(it->first));
		if (it_FD != _fd_nick_list.end())
		{
			result += it_FD->second;
		}
		else
		{
			result += "MISSING";
		} 
	}
	return (result);

}

std::string Server::PrepJchannel(std::string const command)
{
	// Will contain the list of all channels pass into parameters
	std::string jchannel = "";

    // temporary code to remove the PART  in the command
	if (command.find("JOIN") == 0)
		jchannel = command.substr(5);
	else
		jchannel = command;

	// cut the \r\n at the end of the string
	jchannel = jchannel.substr(0, jchannel.length()-2);

	// include a , to help in the next step
	jchannel = jchannel + ",";
	
    if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -------------------------------
    {
        std::cout << BLU;
        std::cout << "[ SERVER::Cmds_join] Prepjchannel" <<  std::endl;
        std::cout << "  command :" << ">" << command << "<" << std::endl;
		std::cout << "  pchannel :" << ">" << jchannel << "<" << std::endl;
        std::cout << NOC;
    } // --------------------------------------------------------------------------------------	
	return (jchannel);
}


void Server::Cmds_join(int const fd_client, std::string const command, std::string const nickname)
{
	// parse command into jchannel
	std::string jchannel = PrepJchannel(command);
	// fullfil the (segment & typec) based on value in pchannel
	std::map<std::string, std::string> segment_typeC = Cmd_channelParse(jchannel);

	// Find IP address
	std::string ip_client = this->_clientList[nickname]->get_ip();
	// Find user
	std::string user_client = this->_clientList[nickname]->get_user();

	std::string hostname = this->_hostname;

	std::string segment;
	std::string typeC;

	// send the messages related to the join & act on channel users & channel existence
	std::map<std::string, std::string>::iterator it(segment_typeC.begin());

	// loop over the channel's
	for ( ; it != segment_typeC.end() ; it++ )
	{
		segment = it->first;
		typeC = it->second;

		{
			// find if the channel is already defined
			std::map<std::string, Channel*>::iterator it = this->_channels.find(segment);

			// insert a new channel or update the channel
			if (it == this->_channels.end())
			{
				//create a new set into the _channel map
				Channel *temp = new Channel(segment, this->_IRCconfig);
				this->_channels.insert(std::pair<std::string, Channel* >(temp->getChannelName(), temp));
	
				// find the newly created record
				std::map<std::string, Channel*>::iterator it = _channels.find(segment);
				//  record the user and the ownership of the channel
				it->second->setChannelConnectedFD(fd_client);
				it->second->setChannelFDMode(fd_client, "O@");
			}
			else // update an existing channel
			{
				// retieve the user Mode to ensure the user has not been already banned
				std::map<std::string, Channel * >::iterator it=this->_channels.begin();
				// block banned user to join the channel

				if (it->second->getChannelConnectedFDMode(fd_client) == "b")	
				{
					// ERR_BANNEDFROMCHAN 474 "<channel> :Cannot join channel (+b)"
					std::string cap_response = ":" + hostname + " 474 " + nickname + " " + typeC + segment + " [+n]\r\n";
					std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
					send(fd_client, cap_response.c_str(), cap_response.length(), 0);
					continue;
				}
				// incase of new connection to the channel, add the new user
				it->second->setChannelConnectedFD(fd_client);
				it->second->setChannelFDMode(fd_client, "o");
			}

			// retrieve the channel's users
			std::string channelUsers = ListConnectedUsers(segment);

			// send 4 messages ---------------------------------------------------------------

			std::string cap_response = "";

			
			// ------------------
			// send first message e.g. :VRO_D1!~VRoch_D1@185.25.195.181 JOIN :#blabla
			cap_response = ":" + nickname + "!~" + user_client + '@' + ip_client + " JOIN " + typeC + segment + "\r\n";
			std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

			send(fd_client, cap_response.c_str(), cap_response.length(), 0);

			
			// ------------------
			// send optional message when topic exist e.g. :
			// >> :helix.oftc.net 332 VRO_D2 #blabla1 :ceci est un channel de test
			// 
			std::string topic = this->_channels[segment]->getTopic();
			if (topic != "")
			{
				cap_response = ":" + hostname + " 332 " + user_client + " " + typeC + segment + " :" + it->second->getTopic() + "\r\n";
				std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

				send(fd_client, cap_response.c_str(), cap_response.length(), 0);
			}


			// ------------------
			// send second message with the list of users e.g : 
			// :kinetic.oftc.net 353 VRO @ #blabla :VRO VRO_D1
			//353     RPL_NAMREPLY     "<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]"

			cap_response = ":" + hostname + " 353 " + nickname + " @ " + typeC + segment + " :" + channelUsers + "\r\n";
			std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

			send(fd_client, cap_response.c_str(), cap_response.length(), 0);

			// ------------------
			// send third message ending up the process of joining e.g. :
			// :kinetic.oftc.net 366 VRO_D1 #blabla :End of /NAMES list.
			//366     RPL_ENDOFNAMES    "<channel> :End of /NAMES list"
			cap_response = ":" + hostname + " 366 " + nickname + " " + typeC + segment + " :End of NAMES list\r\n";
			std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

			send(fd_client, cap_response.c_str(), cap_response.length(), 0);

			// ------------------
			// send fourth message informing about add user e.g. :
			// :exo-debian 324 exo_b #blabla [+n]
			// 324     RPL_CHANNELMODEIS "<channel> <mode> <mode params>"
			cap_response = ":" + hostname + " 324 " + nickname + " " + typeC + segment + " [+n]\r\n";
			std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

			send(fd_client, cap_response.c_str(), cap_response.length(), 0);

			// ------------------
			// send complement message about new user e.g. :
			cap_response = ":" + nickname + "!~" + user_client + '@' + ip_client + " JOIN " + typeC + segment + "\r\n";

			Cmds_inform_Channel(cap_response.c_str(), segment, nickname);

		}
	}
}
