#include "Server.hpp"

void Server::Cmds_CAP(int const newListener, std::string const nickname)
{
    std::string cap_response = "001 " + nickname + " :Welcome to the server " + this->_hostname + "!\r\n";
    std::cout << "[Server->Client]" << cap_response << std::endl;

    send(newListener, cap_response.c_str(), cap_response.length(), 0);

    cap_response = "002 " + nickname + " :Your host is " + this->_hostname + ", version 1.0\r\n";
    std::cout << "[Server->Client]" << cap_response << std::endl;

    send(newListener, cap_response.c_str(), cap_response.length(), 0);


    cap_response = "003 " + nickname + " :This server was created not so long time ago.\r\n";
    std::cout << "[Server->Client]" << cap_response << std::endl;

    send(newListener, cap_response.c_str(), cap_response.length(), 0);

    cap_response = "004 " + nickname + " :Your are welcome. Enjoy!\r\n";
    std::cout << "[Server->Client]" << cap_response << std::endl;

    send(newListener, cap_response.c_str(), cap_response.length(), 0);

    // mode par defaut avant connection a un channel
    // cap_response = nickname + "!" + nickname + "@" + "127.0.0.1 " + "MODE " + nickname + " +i\r\n";
    cap_response = "MODE " + nickname + " +i\r\n";

    std::cout << "[Server->Client]" << cap_response << std::endl;

    send(newListener, cap_response.c_str(), cap_response.length(), 0);

}