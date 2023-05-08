#include "Server.hpp"

// **********************************************************************************************
// Perform the delete of the fd into the channel
void Server::Cmds_quit(const int fd_client)
{
	std::cout << RED << "Cmds_quit fd " << fd_client << NOC << std::endl;
    // find all channels associated to the FD
	std::map<std::string, Channel*>::iterator it(this->_channels.begin());

	for ( ; it != this->_channels.end() ; it++)
	{
		std::cout << "1 " << fd_client << std::endl;
		if (it->second->getChannelConnectedFD(fd_client) == fd_client)
		{
			std::cout << "2 " << fd_client << std::endl;
			quit_channelUpdate(it->first, fd_client);
			std::cout << "3 " << fd_client << std::endl;

			// check if the user deleted was the last one (exclude banned users) = Nb users still connected
			if (it->second->getNbUsers() == 0)
			{
				std::cout << "4 " << fd_client << std::endl;
				// delete the channel
				delete(it->second);
				//std::cout << RED << "Deleted channel " << it->first << NOC << std::endl;
				this->_channels.erase(it);
				// hereafter is required to avoid issues at quit (heap-buffer-overflow)
				it = this->_channels.begin();
				if (it == this->_channels.end())
					return;
			}
		}
	}
}
// **********************************************************************************************
// Perform the delete of the fd into the channel
void Server::quit_channelUpdate(const std::string channel, const int fd_client)
{
	std::cout << RED << "quit_channelUpdate fd " << fd_client << NOC << std::endl;
	if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -------------------------------
    {
        std::cout << BLU;
        std::cout << "[ SERVER::Cmds_quit] quit_channelUpdate" <<  std::endl;
        std::cout << "  channel :" << ">" << channel << "<" << std::endl;
		std::cout << "  fd_client :" << ">" << fd_client << "<" << std::endl;
        std::cout << NOC;
    } // --------------------------------------------------------------------------------------

    // get the nick name
    std::string nickname = "";
    std::map<int, std::string>::iterator it_FD(_fd_nick_list.find(fd_client));
    if (it_FD != _fd_nick_list.end())
    {
        nickname = it_FD->second;
    }



	std::map<std::string, Channel * >::const_iterator it_c(this->_channels.find(channel));

	if (it_c != this->_channels.end())
	{
		if (it_c->second->getChannelConnectedFDMode(fd_client) != "b")
		{
			// delete the user
			//std::cout << RED << "FD " << fd_client << " away from channel "<< it_c->first << NOC << std::endl;
			it_c->second->resetChannelConnectedFD(fd_client);
            // inform the rest of the channel's users
            // ------------------
            // send complement message about quit user
            // :VRO_D1!~VRoch_D1@185.25.195.181 QUIT :
            // Find IP address
            std::string ip_client = this->_clientList[nickname]->get_ip();
            // return the user name of the client
            std::string userName = this->_clientList[nickname]->get_user();
            std::string cap_response = ":" + nickname + "!~" + userName + '@' + ip_client + " QUIT :" + "\r\n";
            Cmds_inform_Channel(cap_response.c_str(), channel, nickname);

		}

		//std::cout << RED << "Remaining FD " << it_c->second->getNbUsers() << " on channel "<< it_c->first << NOC << std::endl;

	}
}

