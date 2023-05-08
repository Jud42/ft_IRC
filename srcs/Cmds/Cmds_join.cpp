#include "Server.hpp"


// **********************************************************************************************
// Retrieve channel's connected users 
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

// **********************************************************************************************
// Prep channel's names extraction
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

	// remove the channels passwords at the end of the command if any
	std::string passwords = "";
	if (jchannel.find(" ") < jchannel.length())
	{
		passwords = jchannel.substr(jchannel.find(" ")+1);
		// truncate the pchannel to keep only channel's names
		jchannel = jchannel.substr(0, jchannel.find(" "));
	}

	// include a , to help in the next step
	jchannel = jchannel + ",";


    if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -------------------------------
    {
        std::cout << BLU;
        std::cout << "[ SERVER::Cmds_join] PrepJchannel" <<  std::endl;
        std::cout << "  command :" << ">" << command << "<" << std::endl;
		std::cout << "  pchannel :" << ">" << jchannel << "<" << std::endl;
        std::cout << NOC;
    } // --------------------------------------------------------------------------------------
	return (jchannel);
}

// **********************************************************************************************
// parse the pchannel to get std::map<std::string, std::string> segment_typeCpass
std::map<std::string, std::string> Server::Cmd_channelPassParse (std::string pchannel, std::string passwords)
{
	if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -------------------------------
    {
        std::cout << BLU;
        std::cout << "[ SERVER::Cmds_part] Cmd_channelparse" <<  std::endl;
		std::cout << "  pchannel :" << ">" << pchannel << "<" << std::endl;
		std::cout << "  passwords :" << ">" << passwords << "<" << std::endl;
        std::cout << NOC;
    } // --------------------------------------------------------------------------------------

	std::map<std::string, std::string> segment_typeCpass;
	std::map<std::string, std::string>::iterator it(segment_typeCpass.begin());

	std::string typeC;
	std::string segment;
	std::string pass;

	// the pchannel alway end by a , as this has been forced in previous function
	if (pchannel.find(",") < pchannel.size())
	{

		while (pchannel != "")
		{

			pass = "";
			// extract the related pass if any
			if (passwords != "")
			{
				pass = passwords.substr(0, passwords.find(","));

				// passwords remaining for next channels
				passwords = passwords.substr(passwords.find(","));
			}

			typeC = pchannel.substr(0, 1);

			// treat the case where a # is set and might be separated from the name
			if (typeC == "#")
			{
				segment = pchannel.substr(1, pchannel.find(",")-1);
			}
			else
			{
				typeC = "";
				segment = pchannel.substr(0, pchannel.find(","));
			}

			// reduce the size of the pchannel for the next cycle
			pchannel = pchannel.substr(pchannel.find(",")+1);
			// reduce the size of passwords
			passwords = passwords.substr(passwords.find(",")+1);
			// attach pass to typeC
			typeC += pass;
		

			it = segment_typeCpass.find(segment);

			if (it == segment_typeCpass.end())
				segment_typeCpass.insert(std::pair<std::string, std::string>(segment, typeC));

		}
	}
	    if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -------------------------------
    {
        std::cout << BLU;
		it = segment_typeCpass.begin();
		for ( ; it != segment_typeCpass.end() ; it++)
		{
        	std::cout << "  segment & typeC :" << ">" << it->first << "<>" << it->second << "<" << std::endl;
		}
        std::cout << NOC;
    } // --------------------------------------------------------------------------------------


	return (segment_typeCpass);
}


// **********************************************************************************************
// Preparation of passwords entered during the join 
const std::string Server::PasswordPrep(std::string const command)
{
	// extract the channels passwords at the end of the command if any
	std::string passwords = command;


	// temporary code to remove the PART  in the command
	if (passwords.find("JOIN ") == 0)
		passwords = passwords.substr(5);

	// cut the \r\n at the end of the passwords
	passwords = passwords.substr(0, passwords.length()-2);

	// remove the channels at the begining of the passwords 
	if (passwords.find(" ") < passwords.length())
	{
		passwords = passwords.substr(passwords.find(" ")+1);
		passwords = passwords + ",";
	}
	else
	{
		passwords = "";
	}

    if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -------------------------------
    {
        std::cout << BLU;
        std::cout << "[ SERVER::Cmds_join] PasswordPrep" <<  std::endl;
        std::cout << "  command :" << ">" << command << "<" << std::endl;
		std::cout << "  passwords :" << ">" << passwords << "<" << std::endl;
        std::cout << NOC;
    } // --------------------------------------------------------------------------------------

	return (passwords);

}


// **********************************************************************************************
// Entry point for JOIN command
void Server::Cmds_join(int const fd_client, std::string const command, std::string const nickname)
{
	std::string jchannel = PrepJchannel(command);
	std::string passwords = PasswordPrep(command);

	// fullfil the (segment & typec) based on value in pchannel
	std::map<std::string, std::string> segment_typeC = Cmd_channelPassParse(jchannel, passwords);

	// find IP address
	std::string ip_client = this->_clientList[nickname]->get_ip();
	// find user
	std::string user_client = this->_clientList[nickname]->get_user();
	// transform hostname as a string form + concatenation usage
	std::string hostname = this->_hostname;

	// key elements
	std::string segment;
	std::string typeC;

	// initialisation
	std::string channelMode = "";
	std::string channelPass = "";
	std::string FDpass = "";

	// ** send the messages related to the join & act on channel users & channel existence
	
	std::map<std::string, std::string>::iterator it_ST(segment_typeC.begin());

	// loop over the channel's
	for ( ; it_ST != segment_typeC.end() ; it_ST++ )
	{
		segment = it_ST->first;
		typeC = it_ST->second;
		FDpass = ""; //password pass by the client irssi

		// split typeC content
		if (typeC.substr(0,1) == "#")
		{
			FDpass = typeC.substr(1);
			typeC = typeC.substr(0, 1);
		}
		else
		{
			FDpass = typeC.substr(0);
			typeC = "";
		}

		// find if the channel is already defined
		std::map<std::string, Channel*>::iterator it_C = this->_channels.find(segment);

		// for existing channels, extract main elements
		if (it_C != this->_channels.end())
		{
		// retrieve the mode(s)
			channelMode = it_C->second->getChannelMode();
		// retrieve the pass
			channelPass = it_C->second->getChannelPass();
		}


		// ** insert a new channel or update the channel

		if (it_C == this->_channels.end()) // insert new channel
		{
			//create a new set into the _channel map
			Channel *temp = new Channel(segment, this->_IRCconfig);
			this->_channels.insert(std::pair<std::string, Channel* >(temp->getChannelName(), temp));


			// find the newly created record
			it_C = _channels.find(segment);
			//  record the user and the ownership of the channel
			it_C->second->setChannelConnectedFD(fd_client);

			// set the channel's default mode
// -----
			it_C->second->setChannelMode("+nt");

			it_C->second->setChannelFDMode(fd_client, "O@");
		}
		else // update an existing channel
		{
			// retieve the user Mode to ensure the user has not been already banned
			std::map<std::string, Channel * >::iterator it=this->_channels.begin();


			// block banned user to join the channels
			if (it->second->getChannelConnectedFDMode(fd_client) == "b")	
			{
				// ERR_BANNEDFROMCHAN 474 "<channel> :Cannot join channel (+b)"
				std::string cap_response = ":" + hostname + " 474 " + nickname + " " + typeC + segment + " [+n]\r\n";
				std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
				send(fd_client, cap_response.c_str(), cap_response.length(), 0);
				continue;
			}

			// use the channel mode to check if join on invite required
			if (channelMode.find("i") < channelMode.length())
			{
				// check if the fd was invited
				if (it->second->checkChannelInvite(fd_client) == false)
				{
					// ERR_INVITEONLYCHAN 473 "<channel> :Cannot join channel (+i)"
					std::string cap_response = ":" + hostname + " 473 " + nickname + " " + typeC + segment + " [+n]\r\n";
					std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
					send(fd_client, cap_response.c_str(), cap_response.length(), 0);
					continue;
				}
			}

			// treat channels set with password
			if (channelMode.find("k") < channelMode.length() && channelPass != FDpass)
			{
				// ERR_BADCHANNELKEY 475 "<channel> :Cannot join channel (+k)"
				std::string cap_response = ":" + hostname + " 475 " + nickname + " " + typeC + segment + " [+n]\r\n";
				std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
				send(fd_client, cap_response.c_str(), cap_response.length(), 0);
				continue;
			}	

			// treat channels set with limits
// -----			
			if (channelMode.find("l") < channelMode.length() && it_C->second->getNbUsers() < ???)
			{
				// ERR_CHANNELISFULL 471 "<channel> :Cannot join channel (+l)"
				std::string cap_response = ":" + hostname + " 471 " + nickname + " " + typeC + segment + " [+n]\r\n";
				std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
				send(fd_client, cap_response.c_str(), cap_response.length(), 0);
				continue;
			}

			// incase of new connection to the channel, add the new FD
			it->second->setChannelConnectedFD(fd_client);
			it->second->setChannelFDMode(fd_client, "o");
		}

		// retrieve the channel's users
		std::string channelUsers = ListConnectedUsers(segment);

		// ** send 4 messages

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
			cap_response = ":" + hostname + " 332 " + user_client + " " + typeC + segment + " :" + it_C->second->getTopic() + "\r\n";
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
