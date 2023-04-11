#include "Server.hpp"

void Server::Cmds_CAP(int const newListener, std::string const nickname)
{
    std::string cap_response = "001 " + nickname + " :Welcome to the server " + this->_hostname + "!\r\n";
    std::cout << "[Server->Client]" << cap_response << std::endl;

    send(newListener, cap_response.c_str(), cap_response.length(), 0);

    cap_response = "MODE exo +i\r\n";
    std::cout << "[Server->Client]" << cap_response << std::endl;
    send(newListener, cap_response.c_str(), cap_response.length(), 0);

}