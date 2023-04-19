#include "Server.hpp"
#include "Channel.hpp"



void Server::Cmds_join(int const fd_client, std::string const command, std::string const nickname)
{
	std::string pchannel = command.substr(5);

    if ("DEBUG" ==_IRCconfig->getConfigValue("DEBUG")) // -------------------------------------
	{
		// retrieve error code of getaddrinfo command
		std::cout << BLU;
		std::cout << "[Server::Cmds_join ]" << std::endl;
        std::cout << " fd_client :" << fd_client << std::endl;
        std::cout << " channel :" << pchannel << std::endl;
    	std::cout << " nickname :" << nickname << std::endl; // WARNING missing info
		std::cout << NOC;
	} // --------------------------------------------------------------------------------------

	int max_segment = 10;
	std::string segment[max_segment];
	std::string typeC[max_segment];
	std::string channelUsers = "";

	// initialise the 10 potentitial new join
	for (int i = 0 ; i < max_segment ; i++)
	{
		segment[i] = "";
		typeC[i] = "";
	}

	int i = 0;
	// identify if manny chanels are transfered in one JOIN and separated by a comma
	if (pchannel.find(",")==0)
	{
		// TBC_VROCH, parse les differents channels demandes
	}
	else
	{
		typeC[i] = pchannel.substr(0, 1);
		segment[i] = pchannel.substr(1, pchannel.find("\r") - 1);
		std::cout << "*"<< segment[i] << "*" <<  std::endl;
	}

	// management of each channels objects (one object per channel)

	for (int i = 0; i < max_segment; i++)
	{
		if (segment[i] == "")
			continue;

		// find if the channel is already defined
		std::cout << RED  << segment[i] << NOC << std::endl;
		std::map<std::string, Channel*>::iterator it = _channels.find(segment[i]);
		if (it == _channels.end())
		{
			//	Create a new set into the _channel map
			std::cout << RED  << "Channel creation" << NOC << std::endl;
			std::cout << RED  << segment[i] << NOC << std::endl;
			Channel *temp = new Channel(segment[i]);
			
			std::cout << RED  << temp->getChannelName() << NOC << std::endl;
			this->_channels.insert(std::pair<std::string, Channel* >(temp->getChannelName(), temp));
			std::cout << RED  << "Channel created" << NOC << std::endl;
		}

		// re-find the current map segment
		it = _channels.find(segment[i]);
		if (it != _channels.end())
		{
			std::cout << RED  << "Channel edited" << NOC << std::endl;
			it->second->setConnectedUser(nickname);
		}

		std::cout << RED  << segment[i] << NOC << std::endl;
		std::cout << RED << " " << NOC << std::endl;

		// add the user to the list of connected users to this channel

			//this->_channels.find(segment[i])->second.setConnectedUser(segment[i]);
		


		//std::cout << "Object :" << this->_channels.find(segment[i])->second.getChannelName() << std::endl;
		//std::cout << "users :" << this->_channels.find(segment[i])->second.getConnectedUsers() << std::endl;


		std::string hostname = this->_hostname;

		//std::string cap_response = "JOIN " + segment[i] + "\r\n";
		//std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

		//send(fd_client, cap_response.c_str(), cap_response.length(), 0);

		// for the channel creator only

		std::string cap_response = "";

	
			cap_response = ":" + nickname + '@' + "10.11.6.4" + " JOIN " + typeC[i] + segment[i] + "\r\n";
			std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

			send(fd_client, cap_response.c_str(), cap_response.length(), 0);


			//353     RPL_NAMREPLY     "<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]"
			// cap_response = ":" + nickname + " 353 " + nickname + " = " + typeC[i] + segment[i] + ":@" + nickname + "\r\n";
			cap_response = ":" + nickname + " 353 " + nickname + " = " + typeC[i] + segment[i] + ":@" + channelUsers + "\r\n";
			std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

			send(fd_client, cap_response.c_str(), cap_response.length(), 0);


			//366     RPL_ENDOFNAMES    "<channel> :End of /NAMES list"
			// cap_response = ":" + hostname + " 366 " + nickname + " " + typeC[i] + segment[i] + " :End of NAMES list\r\n";
			cap_response = ":" + hostname + " 366 " + nickname + " " + typeC[i] + segment[i] + " :End of NAMES list\r\n";
			std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

			send(fd_client, cap_response.c_str(), cap_response.length(), 0);


	}


	}
