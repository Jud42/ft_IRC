#include "Server.hpp"

void Server::Cmds_part(int const fd_client, std::string const command, std::string const nickname)
{
	std::string pchannel = "";
	std::cout << RED << pchannel << NOC << std::endl;
    // temporary code
	if (command.find("PART") == 0)
		pchannel = command.substr(5);
	else
		pchannel = command;
	//end of temporary code

	// if the part is issued from a channel session, format is different 
	// this is to keep only the information required after the :
	if (pchannel.find(":") )
	{
		pchannel = pchannel.substr(pchannel.find(":")+1);
		
	}

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
			typeC[i] = pchannel.substr(0, 1);
			// treat the case where a # is set and might be separated from the name
			if (typeC[i] == "#")
			{
			segment[i] = pchannel.substr(1, pchannel.find(",")-1);
			}
			else
			{
				typeC[i] = "";
				segment[i] = pchannel.substr(0, pchannel.find(",")-1);
			}
			// reduce the size of the pchannel for the next cycle
			pchannel = pchannel.substr(pchannel.find(",")+1);
		}
		else
		{
			// treat the case where a # is set and might be separated from the name
			typeC[i] = pchannel.substr(0, 1);
			if (typeC[i] == "#")
			{
			segment[i] = pchannel.substr(1, pchannel.find("/r")-1);
			}
			else
			{
				typeC[i] = "";
				segment[i] = pchannel.substr(0, pchannel.find("/r")-1);
			}
			pchannel = "";
			break;
		}
	}
	

	for (int i = 0 ; i < max_segment ; i++ )
	{
		if (segment[i] == "")
			break;

		// Find IP address
		std::string ip_client = this->_clientList[nickname]->get_ip();

		// send first message informing about quit user e.g. :
		// :exo_b!exo_b@127.0.0.1 PART #blabla
		std::string cap_response = ":" + nickname + "!" + nickname + '@' + ip_client + " PART " + segment[i] + "\r\n";
		std::cout << RED << fd_client << " [Server->Client]" << cap_response << NOC << std::endl;

		send(fd_client, cap_response.c_str(), cap_response.length(), 0);


		// **** delete channel's user and/or channel itself

		// retieve the user Mode to ensure he's not banned
		std::map<std::string, Channel * >::iterator it=this->_channels.begin();

		if (it->second->getConnectedUsersMode(nickname) != "b")		
		{
			// delete the user
			std::cout << RED << "User " << nickname << " away from channel "<< it->first << NOC << std::endl;
			it->second->resetConnectedUser(nickname);
		}
		// check if the user deleted whas the last one (exclude banned users)
		
		std::cout << RED << "Nb users still connected " << it->second->getNbUsers() << " to "<< segment[i] << NOC << std::endl;
		if (it->second->getNbUsers() == 0)
		{
		// delete the channel
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

}
