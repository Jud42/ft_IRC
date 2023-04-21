#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"



void Server::Cmds_join(int const fd_client, std::string const command, std::string const nickname)
{
	std::string pchannel = "";
	// temporary code
	if (command.find("JOIN") == 0)
		pchannel = command.substr(5);
	else
		pchannel = command;


	std::cout << YEL << pchannel << NOC << std::endl;		
	//end of temporary code

	// Find IP address
	std::string ip_client = this->_clientList[nickname]->get_ip();
	// Find user
	std::string user_client = this->_clientList[nickname]->get_user();


	std::string hostname = this->_hostname;

	int max_segment = MAX_JOINS_PER_LINE;
	std::string segment[max_segment];
	std::string typeC[max_segment];
	

	// initialise the MAX_JOINS_PER_LINE potentitial new join
	for (int i = 0 ; i < max_segment ; i++)
	{
		segment[i] = "";
		typeC[i] = "";
	}


	// detect and parse each iteration of channels in one command
	for (int i = 0 ; i < max_segment ; i++)
	{
		if (pchannel.find(",", 0) < pchannel.size())
		{		
			typeC[i] = pchannel.substr(0, 1);
			segment[i] = pchannel.substr(1, pchannel.find(",")-1);
			// reduce the size of the pchannel for the next cycle
			pchannel = pchannel.substr(pchannel.find(",")+1);
		}
		else
		{
			typeC[i] = pchannel.substr(0, 1);
			segment[i] = pchannel.substr(1, pchannel.find("\r")-1);
			pchannel = "";
			break;
		}
	}


	for (int i = 0 ; i < max_segment ; i++)
	{
		if (segment[i] == "")
			break;

		std::cout << YEL << i << "=" << segment[i] << NOC << std::endl;

		// find if the channel is already defined
		std::map<std::string, Channel*>::iterator it = _channels.find(segment[i]);

		// insert a new channel
		if (it == _channels.end())
		{
			//	Create a new set into the _channel map
			Channel *temp = new Channel(segment[i], this->_IRCconfig);
			this->_channels.insert(std::pair<std::string, Channel* >(temp->getChannelName(), temp));
			// find the newly created record
			std::map<std::string, Channel*>::iterator it = _channels.find(segment[i]);
			//  record the user and the ownership of the channel
			it->second->setConnectedUser(nickname);
			it->second->setChannelMode(nickname, "O#");
		}
		else
		{
			// retieve the user Mode to ensure he's not banned
			std::map<std::string, Channel * >::iterator it=this->_channels.begin();
			// block banned user to join the channel
			if (it->second->getConnectedUsersMode(nickname) == "")	
			{
				// ERR_BANNEDFROMCHAN 474 "<channel> :Cannot join channel (+b)"
				std::string cap_response = ":" + nickname + "!" + user_client + '@' + ip_client + " 474 " + typeC[i] + segment[i] + "\r\n";
				std::cout << RED << fd_client << " [Server->Client]" << cap_response << NOC << std::endl;
				send(fd_client, cap_response.c_str(), cap_response.length(), 0);
				return;
			}
			// incase of new connection to the channel, add the new user
			it->second->setConnectedUser(nickname);
			it->second->setChannelMode(nickname, "o");
		}

		// send 4 messages

		std::string cap_response = "";
		
		
		// send first message e.g. : :Nickexo_a!User_exo_a@127.0.0.1 JOIN #blabla
		cap_response = ":" + nickname + "!" + user_client + '@' + ip_client + " JOIN " + typeC[i] + segment[i] + "\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

		send(fd_client, cap_response.c_str(), cap_response.length(), 0);

		// retrieve the list of users attached to the channel
		std::string channelUsers = this->_channels[segment[i]]->getConnectedUsers();

		// return the user name of the client
		std::string userName = this->_clientList[nickname]->get_user();

		// send second message with the list of users e.g : 
		// :exo-debian 353 Nickexo_a = #blabla :@Nickexo_a
		//353     RPL_NAMREPLY     "<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]"
		//cap_response = ":" + nickname + " 353 " + nickname + " = " + typeC[i] + segment[i] + ":@" + channelUsers + "\r\n";
		cap_response = ":" + hostname + " 353 " + nickname + " = " + typeC[i] + segment[i] + ":@" + channelUsers + "\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

		send(fd_client, cap_response.c_str(), cap_response.length(), 0);


		// send third message ending up the process of joining e.g. :
		// :exo-debian 366 Nickexo_a #blabla :End of NAMES list
		//366     RPL_ENDOFNAMES    "<channel> :End of /NAMES list"
		//cap_response = ":" + hostname + " 366 " + nickname + " " + typeC[i] + segment[i] + " :End of NAMES list\r\n";
		cap_response = ":" + hostname + " 366 " + nickname + " " + typeC[i] + segment[i] + " :End of NAMES list\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

		send(fd_client, cap_response.c_str(), cap_response.length(), 0);

		// send fourth message informing about add user e.g. :
		// :exo-debian 324 exo_b #blabla [+n]
		// 324     RPL_CHANNELMODEIS "<channel> <mode> <mode params>"
		cap_response = ":" + hostname + " 324 " + nickname + " " + typeC[i] + segment[i] + " [+n]\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

		send(fd_client, cap_response.c_str(), cap_response.length(), 0);

	}


}
