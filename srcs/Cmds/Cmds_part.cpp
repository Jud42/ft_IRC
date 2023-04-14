#include "Server.hpp"

void Server::Cmds_part(int const fd_client, std::string const command, std::string const nickname)
{
    std::string pchannel = command.substr(5);
	std::string hostname = this->_hostname;
	std::string segment[10];
	std::string typeC[10];

	if ("DEBUG" ==_IRCconfig->getConfigValue("DEBUG")) // -------------------------------------
	{
		// retrieve error code of getaddrinfo command 
		std::cout << BLU;
        std::cout << "[ Server::Cmds_part ]" << fd_client << std::endl;
        std::cout << "fd_client :" << fd_client << std::endl;
        std::cout << "channel :" << pchannel << std::endl;
    	std::cout << "nickname :" << nickname << std::endl; // WARNING missing info
		std::cout << NOC;
	} // --------------------------------------------------------------------------------------

	// identify if manny chanels are transfered in one PART and sepparated by a comma
	if (pchannel.find(",")==0)
	{
		// extract all channels - max 10;
		
	}
	else
	{
		typeC[0] = pchannel.substr(0, 1);
		segment[0] = pchannel.substr(1);
	}
	std::string cap_response = "PART " + pchannel + "\r\n";
	cap_response = nickname + "!" + nickname + '@' + hostname + " PART " + typeC[0] + segment[0] + "\r\n";
    //std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
	
	send(fd_client, cap_response.c_str(), cap_response.length(), 0);

}