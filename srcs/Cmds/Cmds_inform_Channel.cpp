#include "Server.hpp"

void Server::Cmds_inform_Channel(std::string const message, std::string const channel, std::string const exceptUser)
{
    if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -------------------------------
    {
        std::cout << BLU;
        std::cout << "[ SERVER::Cmds_inform_Channel ]" <<  std::endl;
        std::cout << "  ExceptUser :" << exceptUser << std::endl;
        std::cout << NOC;
    } // --------------------------------------------------------------------------------------

    // the purpose of this is to inform each user recorded into the cannel except :
    // - the user that is at the origin of message propagation request
    // - all the users banned are already excluded from the list
    
    std::cout << "[ SERVER::Cmds_inform_Channel ] " << channel <<  std::endl;

    // will contain an abstract from the channel 
    std::map<std::string, std::string>channelClients;


    // find the channel
    std::map<std::string, Channel*>::iterator it_c(_channels.find(channel));

    if (it_c->first == channel)
    {
        // retrive the list of all users attached to the channel
        channelClients = it_c->second->getMapUsers();        
    }

    std::map <std::string, std::string>::iterator it = channelClients.begin();
    std::cout << " it :" << it->first  << std::endl;

    // turn to send message
    for( ; it != channelClients.end() ; ++it)
    {
        // the user originating the message in not selected for the "rest of channel" message
        if (it->first != exceptUser)
        {
            std::cout << RED << " User selected :" << it->first << NOC << std::endl;
            std::map <int, std::string>::const_iterator it_FD = this->_fd_nick_list.begin();
            
            // look for channel
            for( ; it_FD != this->_fd_nick_list.end() ; ++it_FD)
            {
                if (it_FD->second == it->first)
                {
                    // channel for information
                    int fd_dest = it_FD->first;
                    std::cout << RED << " it_FD->first :" << it_FD->first << NOC << std::endl;

                    send(fd_dest, message.c_str(), message.length(), 0);
                    std::cout << fd_dest << " [Server->Client]" << message << std::endl;
                }
            }
        }

    }   

}