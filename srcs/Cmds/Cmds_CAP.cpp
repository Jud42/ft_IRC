#include "Server.hpp"

void Server::Cmds_CAP(int const fd_client, std::string const nickname)
{
	std::string hostname = this->_hostname;
    std::string cap_response = ":" + hostname + " 001 " + nickname + " :Welcome to the server " + this->_hostname + "!\r\n";
    std::cout << fd_client << "[Server->Client]" << cap_response << std::endl;

    send(fd_client, cap_response.c_str(), cap_response.length(), 0);

    cap_response = ":" + hostname + " 002 " + nickname + " :Your host is " + this->_hostname + ", version 1.0\r\n";
    std::cout << fd_client << "[Server->Client]" << cap_response << std::endl;

    send(fd_client, cap_response.c_str(), cap_response.length(), 0);


    cap_response = ":" + hostname + " 003 " + nickname + " :This server was created not so long time ago.\r\n";
    std::cout << fd_client << "[Server->Client]" << cap_response << std::endl;

    send(fd_client, cap_response.c_str(), cap_response.length(), 0);

    cap_response = ":" + hostname + " 004 " + nickname + " :Your are welcome. Enjoy!\r\n";
    std::cout << fd_client << "[Server->Client]" << cap_response << std::endl;

    send(fd_client, cap_response.c_str(), cap_response.length(), 0);

	// >> :kinetic.oftc.net 376 vanilou :End of /MOTD command.

	cap_response =  ":" + hostname + " 376 " + nickname + " :End of /MOTD command.\r\n";
	std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
	send(fd_client, cap_response.c_str(), cap_response.length(), 0);

    // mode par defaut avant connection a un channel
    // :vanilou!~vanilouH@185.25.195.181 MODE vanilou :+i

    cap_response = ":" + nickname + "!~" + this->_clientList[nickname]->get_user() + "@" +  " MODE " + nickname + " +i\r\n";

    std::cout << fd_client << "[Server->Client]" << cap_response << std::endl;

    send(fd_client, cap_response.c_str(), cap_response.length(), 0);

}
