#include "Server.hpp"


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

	for ( ; it != segment_typeC.end() ; it++ )
	{
		segment = it->first;
		typeC = it->second;

		{
			// find if the channel is already defined
			std::map<std::string, Channel*>::iterator it = _channels.find(segment);

			// insert a new channel or update the channel
			if (it == _channels.end())
			{
				//create a new set into the _channel map
				Channel *temp = new Channel(segment, this->_IRCconfig);
				this->_channels.insert(std::pair<std::string, Channel* >(temp->getChannelName(), temp));
				// find the newly created record
				std::map<std::string, Channel*>::iterator it = _channels.find(segment);
				//  record the user and the ownership of the channel
				it->second->setConnectedUser(nickname);
				it->second->setChannelMode(nickname, "O@");
			}
			else
			{
				// retieve the user Mode to ensure the user has not been already banned
				std::map<std::string, Channel * >::iterator it=this->_channels.begin();
				// block banned user to join the channel
				if (it->second->getConnectedUsersMode(nickname) == "b")	
				{
					//-->TBC
					// ERR_BANNEDFROMCHAN 474 "<channel> :Cannot join channel (+b)"
					std::string cap_response = ":" + nickname + "!" + user_client + '@' + ip_client + " 474 " + typeC + segment + "\r\n";
					std::cout << RED << fd_client << " [Server->Client]" << cap_response << NOC << std::endl;
					send(fd_client, cap_response.c_str(), cap_response.length(), 0);
					continue;
				}
				// incase of new connection to the channel, add the new user
				it->second->setConnectedUser(nickname);
				it->second->setChannelMode(nickname, "o");
			}

			// send 4 messages ---------------------------------------------------------------

			std::string cap_response = "";
			
			// ------------------
			// send first message e.g. :VRO_D1!~VRoch_D1@185.25.195.181 JOIN :#blabla
			cap_response = ":" + nickname + "!~" + user_client + '@' + ip_client + " JOIN " + typeC + segment + "\r\n";
			std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

			send(fd_client, cap_response.c_str(), cap_response.length(), 0);

			// retrieve the list of FD attached to the channel
			std::string channelUsers = this->_channels[segment]->getChannelFDModeMap();

			// return the user name of the client
			std::string userName = this->_clientList[nickname]->get_user();

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
			std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
			Cmds_inform_Channel(cap_response.c_str(), segment, nickname);

		}
	}
}
