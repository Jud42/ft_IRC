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
	//end of temporary code

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


	// read each iteration of channels in one command
	std::cout << YEL << " find " << NOC << std::endl;
	for (int i = 0 ; i < max_segment ; i++)
	{
		std::cout << YEL << i << " find p =" << pchannel.find(",", 0) << NOC << std::endl;
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
			segment[i] = pchannel.substr(1, pchannel.find("\r"));
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
			it->second->setChannelMode(nickname, "#O");
			
		}
		else
		{
			// incase of new connection to the channel, add the new user
			it->second->setConnectedUser(nickname);
			it->second->setChannelMode(nickname, " i");
		}

		// send 3 messages

		std::string cap_response = "";
		

		// Find IP address
		std::string ip_client = this->_clientList[nickname]->get_ip();

		// send first message e.g. : 12:36 -!- D1vroch [10.11.6.4] has joined #blabla
		cap_response = ":" + segment[i] + '@' + ip_client + " JOIN " + typeC[i] + segment[i] + "\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

		send(fd_client, cap_response.c_str(), cap_response.length(), 0);

		// retrieve the list of users attached to the channel
		std::string channelUsers = this->_channels[segment[i]]->getConnectedUsers();

		// return the user name of the client
		std::string userName = this->_clientList[nickname]->get_user();
		
		std::cout << YEL << "*" << channelUsers << NOC << "*";

		// send second message with the list of users e.g : 
		// :exo-debian 353 exo_a1681845229 = #blabla :@exo_a exo_a1681845229
		//353     RPL_NAMREPLY     "<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]"
		//cap_response = ":" + nickname + " 353 " + nickname + " = " + typeC[i] + segment[i] + ":@" + channelUsers + "\r\n";
		cap_response = ":" + segment[i] + " 353 " + userName + " = " + typeC[i] + segment[i] + ":@" + channelUsers + "\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

		send(fd_client, cap_response.c_str(), cap_response.length(), 0);


		// send third message ending up the process of joining
		//366     RPL_ENDOFNAMES    "<channel> :End of /NAMES list"
		//cap_response = ":" + hostname + " 366 " + nickname + " " + typeC[i] + segment[i] + " :End of NAMES list\r\n";
		cap_response = ":" + segment[i] + " 366 " + nickname + " " + typeC[i] + segment[i] + " :End of NAMES list\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

		send(fd_client, cap_response.c_str(), cap_response.length(), 0);


	}


	}
