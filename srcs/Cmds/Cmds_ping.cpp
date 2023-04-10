#include "Server.hpp"

void Server::Cmds_ping(int const newListener)
{
    //int snd; // size of the sent message

    std::string hostname = this->_hostname;
    std::string cap_response = "PONG " + hostname + " 127.0.0.1\r\n";
    
    std::cout << "[Server->Client]" << cap_response << std::endl;

    //snd = 
    send(newListener, cap_response.c_str(), cap_response.length(), 0);
}