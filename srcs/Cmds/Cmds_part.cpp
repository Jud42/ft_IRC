#include "Server.hpp"

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



void Server::Cmds_part(int const fd_client, std::string const command, std::string const nickname)
{

	// parse command into pchannel
	std::string pchannel = PrepPchannel(command);
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


	// read each iteration of channels in one command line
	for (int i = 0 ; i < max_segment ; i++)
	{
		if (pchannel.find(",") < pchannel.size())
		{
			std::cout << YEL << "pchannel 1.1 " << "|" << pchannel << "|" << NOC << std::endl;
			typeC[i] = pchannel.substr(0, 1);
			// treat the case where a # is set and might be separated from the name
			if (typeC[i] == "#")
			{
			segment[i] = pchannel.substr(1, pchannel.find(",")-1);
			std::cout << YEL << "Case 1" << typeC[i] << "|" << segment[i]<< "|" << NOC << std::endl;
			}
			else
			{
				typeC[i] = "";
			std::cout << YEL << "Case 2" << " pchannel " << pchannel << NOC << std::endl;				
				segment[i] = pchannel.substr(0, pchannel.find(","));
			std::cout << YEL << "Case 2" << typeC[i] << "|" << segment[i]<< "|" << NOC << std::endl;
			}
			std::cout << YEL << typeC[i] << "|" << segment[i] << NOC << std::endl;
			// reduce the size of the pchannel for the next cycle
			pchannel = pchannel.substr(pchannel.find(",")+1);
			std::cout << YEL << "pchannel 1.2 " << "|" << pchannel << "|" << NOC << std::endl;
		}
		else
		{
			// end of line treatment
			// treat the case where a # is set and might be separated from the name
			std::cout << YEL << "pchannel 2.1 " << "|" << pchannel << "|" << NOC << std::endl;
			typeC[i] = pchannel.substr(0, 1);
			if (typeC[i] == "#")
			{
			segment[i] = pchannel.substr(1);
			std::cout << YEL << "Case 3" << typeC[i] << "|" << segment[i]<< "|" << NOC << std::endl;
			}
			else
			{
				typeC[i] = "";
				segment[i] = pchannel.substr(0);
			std::cout << YEL << "Case 4" << typeC[i] << "|" << segment[i]<< "|" << pchannel.find("/r") << NOC << std::endl;
			}
			std::cout << YEL << typeC[i] << "|" << segment[i] << NOC << std::endl;
			pchannel = "";
			break;
		}
	}
	
	// send the messages related to the part
	for (int i = 0 ; i < max_segment ; i++ )
	{
		if (segment[i] == "")
			continue;

		// Find IP address
		std::string ip_client = this->_clientList[nickname]->get_ip();
		// return the user name of the client
		std::string userName = this->_clientList[nickname]->get_user();

		// ------------------
		// send first message informing about quit user e.g. :
		// :VRO_D1!~VRoch_D1@185.25.195.181 PART #blabla
		std::string cap_response = ":" + nickname + "!~" + userName + '@' + ip_client + " PART " + typeC[i] + segment[i] + "\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

		send(fd_client, cap_response.c_str(), cap_response.length(), 0);


		// ------------------
		// send complement message about part user (same message as upper)
		// :VRO!~VRoch@185.25.195.181 PART #blabla
		cap_response = ":" + nickname + "!~" + userName + '@' + ip_client + " PART " + typeC[i] + segment[i] + "\r\n";
		std::cout << YEL << "AV Cmds_inform_Channel" << segment[i] << "|" << nickname << NOC << std::endl;
		Cmds_inform_Channel(cap_response.c_str(), segment[i], nickname);
		std::cout << YEL << " Apres inform channel" << NOC << std::endl;

	}

	// **** delete channel's user and/or channel itself

	// retieve the user Mode to ensure he's not banned
	std::map<std::string, Channel * >::iterator it(this->_channels.begin());

	if (it->second->getConnectedUsersMode(nickname) != "b")		
	{
		// delete the user
		std::cout << RED << "User " << nickname << " away from channel "<< it->first << NOC << std::endl;
		it->second->resetConnectedUser(nickname);
	}
	// check if the user deleted whas the last one (exclude banned users)
	
	//std::cout << RED << "Nb users still connected " << it->second->getNbUsers() << " to "<< segment[i] << NOC << std::endl;
	if (it->second->getNbUsers() == 0)
	{
	// delete the channel
	std::cout << RED << "Deleted channel " << it->first << NOC << std::endl;
	it->second->~Channel();
	this->_channels.erase(it);
	}

	if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -------------------------------
	{
		std::cout << BLU;
		it = this->_channels.begin();
		std::cout << "[ SERVER::join ]" <<  std::endl;
		for ( ; it != this->_channels.end() ; it++)
		{
			std::cout << " remaining open channels :" << it->first << std::endl;
		}
		std::cout << NOC;
	} // --------------------------------------------------------------------------------------

	

}
