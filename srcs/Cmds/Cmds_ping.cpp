#include "Server.hpp"

void Server::Cmds_ping(int const fd_client)
{

    // prepare elements for the answer
    std::string hostname = this->_hostname;
    std::string ip_server = this->_ipstr;
    std::string cap_response = "PONG " + hostname + " " + ip_server + "\r\n";
    
    // print internally the answer for information
    std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

    // send message to the client
    send(fd_client, cap_response.c_str(), cap_response.length(), 0);
}