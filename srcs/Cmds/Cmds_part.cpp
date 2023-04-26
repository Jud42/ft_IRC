#include "Server.hpp"
#include <map>

std::string Server::PrepPchannel(std::string const command)
{
	// Will contain the list of all channels pass into parameters
	std::string pchannel = "";

    // temporary code to remove the PART  in the command
	if (command.find("PART") == 0)
		pchannel = command.substr(5);
	else
		pchannel = command;

	// cut the \r\n at the end of the string
	pchannel = pchannel.substr(0, pchannel.length()-2);

	// if the part is issued from a channel session, format is different 
	// this is to keep only the information required after the :
	if (pchannel.find(":") )
	{
		pchannel = pchannel.substr(pchannel.find(":")+1);	
	}
	// include a , to help in the next step
	pchannel = pchannel + ",";
	
    if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -------------------------------
    {
        std::cout << BLU;
        std::cout << "[ SERVER::Cmds_part] PrepPchannel" <<  std::endl;
        std::cout << "  command :" << ">" << command << "<" << std::endl;
		std::cout << "  pchannel :" << ">" << pchannel << "<" << std::endl;
        std::cout << NOC;
    } // --------------------------------------------------------------------------------------	
	return (pchannel);
}

std::map<std::string, std::string> Server::Cmd_pchannelPart (std::string pchannel)
{
	if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -------------------------------
    {
        std::cout << BLU;
        std::cout << "[ SERVER::Cmds_part] Cmd_pchannelPart" <<  std::endl;
		std::cout << "  pchannel :" << ">" << pchannel << "<" << std::endl;
        std::cout << NOC;
    } // --------------------------------------------------------------------------------------		

	std::map<std::string, std::string> segment_typeC;
	std::map<std::string, std::string>::iterator it(segment_typeC.begin());

	std::string typeC;
	std::string segment;

	while (pchannel != "")
	{
		// the pchannel alway end by a , as this has been forced in previous function
		if (pchannel.find(",") < pchannel.size())
		{
			typeC = pchannel.substr(0, 1);
			// treat the case where a # is set and might be separated from the name
			if (typeC == "#")
			{
			segment = pchannel.substr(1, pchannel.find(",")-1);
			std::cout << YEL << "Case 1" << typeC << "|" << segment<< "|" << NOC << std::endl;
			}
			else
			{
				typeC = "";
			std::cout << YEL << "Case 2" << " pchannel " << pchannel << NOC << std::endl;				
				segment = pchannel.substr(0, pchannel.find(","));
			std::cout << YEL << "Case 2" << typeC << "|" << segment<< "|" << NOC << std::endl;
			}
			std::cout << YEL << typeC << "|" << segment << NOC << std::endl;
			// reduce the size of the pchannel for the next cycle
			pchannel = pchannel.substr(pchannel.find(",")+1);
			std::cout << YEL << "pchannel 1.2 " << "|" << pchannel << "|" << NOC << std::endl;
		}

		it = segment_typeC.find(segment);
		if (it == segment_typeC.end())
			segment_typeC.insert(std::pair<std::string, std::string>(segment, typeC));


	}
	    if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -------------------------------
    {
        std::cout << BLU;
		it = segment_typeC.begin();
		for ( ; it != segment_typeC.end() ; it++)
		{
        	std::cout << "  segment & typeC :" << ">" << it->first << "<>" << it->second << "<" << std::endl;
		}
        std::cout << NOC;
    } // --------------------------------------------------------------------------------------	


	return (segment_typeC);
}



void Server::Cmds_part(int const fd_client, std::string const command, std::string const nickname)
{

	// parse command into pchannel
	std::string pchannel = PrepPchannel(command);
	std::map<std::string, std::string> segment_typeC = Cmd_pchannelPart(pchannel);
	std::string hostname = this->_hostname;
	std::string segment = "";
	std::string typeC = "";

	// send the messages related to the part & act on channel users & channel existence
	std::map<std::string, std::string>::iterator it(segment_typeC.begin());

	for ( ; it != segment_typeC.end() ; it++ )
	{
		segment = it->first;
		typeC = it->second;

		// Find IP address
		std::string ip_client = this->_clientList[nickname]->get_ip();
		// return the user name of the client
		std::string userName = this->_clientList[nickname]->get_user();

		// ------------------
		// send first message informing about quit user e.g. :
		// :VRO_D1!~VRoch_D1@185.25.195.181 PART #blabla
		std::string cap_response = ":" + nickname + "!~" + userName + '@' + ip_client + " PART " + typeC + segment + "\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

		send(fd_client, cap_response.c_str(), cap_response.length(), 0);

		// ------------------
		// send complement message about part user (same message as upper)
		// :VRO!~VRoch@185.25.195.181 PART #blabla
		cap_response = ":" + nickname + "!~" + userName + '@' + ip_client + " PART " + typeC + segment + "\r\n";
		std::cout << YEL << "AV Cmds_inform_Channel" << segment << "|" << nickname << NOC << std::endl;
		Cmds_inform_Channel(cap_response.c_str(), segment, nickname);
		std::cout << YEL << " Apres inform channel" << NOC << std::endl;

	

		// **** delete channel's user and/or channel itself

		// retieve the user Mode to ensure he's not banned
		std::map<std::string, Channel * >::iterator it_c(this->_channels.find(segment));

		if (it_c->second->getConnectedUsersMode(nickname) != "b")		
		{
			// delete the user
			std::cout << RED << "User " << nickname << " away from channel "<< it_c->first << NOC << std::endl;
			it_c->second->resetConnectedUser(nickname);
		}
		// check if the user deleted whas the last one (exclude banned users)

		// Nb users still connected
		if (it_c->second->getNbUsers() == 0)
		{
		// delete the channel
		std::cout << RED << "Deleted channel " << it->first << NOC << std::endl;
		it_c->second->~Channel();
		this->_channels.erase(it_c);
		}

		if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -------------------------------
		{
			std::cout << BLU;
			it_c = this->_channels.begin();
			std::cout << "[ SERVER::join ]" <<  std::endl;
			for ( ; it_c != this->_channels.end() ; it_c++)
			{
				std::cout << " remaining open channels :" << it->first << std::endl;
			}
			std::cout << NOC;
		}
	} // --------------------------------------------------------------------------------------

	

}
