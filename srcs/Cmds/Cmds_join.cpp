#include "Server.hpp"

void Server::Cmds_join(int const fd_client, std::string const command, std::string const nickname)
{
	std::string pchannel = command.substr(5);

    if ("DEBUG" ==_IRCconfig->getConfigValue("DEBUG")) // -------------------------------------
	{
		// retrieve error code of getaddrinfo command
		std::cout << BLU;
		std::cout << "[Server::Cmds_join ]" << fd_client << std::endl;
        std::cout << " fd_client :" << fd_client << std::endl;
        std::cout << " channel :" << pchannel << std::endl;
    	std::cout << " nickname :" << nickname << std::endl; // WARNING missing info
		std::cout << NOC;
	} // --------------------------------------------------------------------------------------

	std::string segment[10];
	std::string typeC[10];

	// initialise the 140 potentitial new join
	for (int i = 0 ; i < 10 ; i++)
	{
		segment[i] = "";
		typeC[i] = "";
	}

	// identify if manny chanels are transfered in one JOIN and separated by a comma
	if (pchannel.find(",")==0)
	{



		// extract all channels - max 10;
		// parse the pchannel

	}
	else
	{
		int i = 0;
		typeC[i] = pchannel.substr(0, 1);
		segment[i] = pchannel.substr(1);
	}

	// management fo the channels objects (one object per channel)

	for (int i = 0; i < 10; i++)
	{
		if (segment[i] == "")
			continue;

		// find if the channel is already defined
		std::map<std::string, Channel>::iterator it = this->_channels.find(segment[i]);
		bool channelAlreadyDefined = false;
		if (it != this->_channels.end())
		{
			// modify the existing object
			this->_channels.find(segment[i])->second.getNbConnection();
			channelAlreadyDefined = true;
		}
		else
		{
			// create a new map record and by consequence a new channel object
			this->_channels[segment[i]]=(Channel(segment[i]));
			// add the user to the list of connected users to this channel
			this->_channels.find(segment[i])->second.setConnectedUser(nickname);
		}


		std::cout << "Object :" << this->_channels.find(segment[i])->second.getChannelName() << std::endl;
		std::cout << "users :" << this->_channels.find(segment[i])->second.getConnectedUsers() << std::endl;


		std::string hostname = this->_hostname;

		//std::string cap_response = "JOIN " + segment[i] + "\r\n";
		//std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

		//send(fd_client, cap_response.c_str(), cap_response.length(), 0);

		// for the channel creator only

		std::string cap_response = "";

		if (channelAlreadyDefined == false)
		{
			//12:28 -!- vroch [~vroch@freenode-o6d.g28.dc9e5h.IP] has joined #blabla
			//12:28 [Users #blabla]
			//12:28 [@vroch]
			//12:28 -!- Irssi: #blabla: Total of 1 nicks [1 ops, 0 halfops, 0 voices, 0         normal]
			//12:28 -!- Channel #blabla created Fri Apr 14 12:28:33 2023
			//12:28 -!- Irssi: Join to #blabla was synced in 0 secs

			
			cap_response = ":" + nickname + "!" + nickname + '@' + "127.0.0.1" + " JOIN " + typeC[i] + segment[i] + "\r\n";
			std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

			send(fd_client, cap_response.c_str(), cap_response.length(), 0);

		}
		else
		{

		}

			cap_response = "332 " + typeC[i] + segment[i] + " :this is my channel \r\n";
			std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

			send(fd_client, cap_response.c_str(), cap_response.length(), 0);


			//353     RPL_NAMREPLY     "<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]"
			cap_response = "353 " + typeC[i] + segment[i] + ": [@" + nickname + "]\r\n";
			std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

			send(fd_client, cap_response.c_str(), cap_response.length(), 0);






	}


	}
