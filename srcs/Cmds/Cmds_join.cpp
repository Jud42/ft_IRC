#include "Server.hpp"

void Server::Cmds_join(int const fd_client, std::string const pchannel, std::string const nickname)
{
    if ("DEBUG" ==_IRCconfig->getConfigValue("DEBUG")) // -------------------------------------
	{
		// retrieve error code of getaddrinfo command 
		std::cout << BLU;
        std::cout << "fd_client :" << fd_client << std::endl;
        std::cout << "channel :" << pchannel << std::endl;
    	std::cout << "nickname :" << nickname << std::endl; // WARNING missing info
		std::cout << NOC;
	} // --------------------------------------------------------------------------------------

	std::string nick = "vroch"; // to be deleted once the problem with nickname solved.
	// replace in the hereafter code nick by nickname


	std::string segment[10];
	char types[10];

	// initialise
	for (int i = 0 ; i < 10 ; i++)
	{
		segment[i] = "";
		types[i] = ' ';
	}

	// identify if manny chanels are transfered in one JOIN and sepparated by a comma
	if (pchannel.find(",")==0)
	{
		// extract all channels - max 10;
		
	}
	else
	{
		types[0] = pchannel[0];
		segment[0] = pchannel.substr(1);
	}
	
	// management fo the channels objects (one object per channel)


	
	// find if the channel is already defined
	std::map<std::string, Channel>::iterator it = this->_channels.find(segment[0]);
	if (it != this->_channels.end())
	{
		// modifiy the existing object
		this->_channels.find(segment[0])->second.getNbConnection();

	}
	else
	{
		// create a new map record and by consequence a new channel object
		this->_channels[segment[0]]=(Channel(segment[0]));
		// add the user to the list of connected users to this channel
		this->_channels.find(segment[0])->second.setConnectedUser(nick);

		

	}


	std::cout << "Object :" << this->_channels.find(segment[0])->second.getChannelName() << std::endl;
	std::cout << "users :" << this->_channels.find(segment[0])->second.getConnectedUsers() << std::endl;


	std::string hostname = this->_hostname;

    std::string cap_response = "JOIN " + segment[0] + "\r\n";
    std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

    send(fd_client, cap_response.c_str(), cap_response.length(), 0);

	//353     RPL_NAMREPLY     "<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]"
	cap_response = "353 " + segment[0] + " :" + nick + "\r\n";
    std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

	send(fd_client, cap_response.c_str(), cap_response.length(), 0);
	

	}