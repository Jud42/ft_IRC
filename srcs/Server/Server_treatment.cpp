#include "Server.hpp"

void Server::treatment(int client_fd)
{
    int res = 0;

    // struct sockaddr client_addr;
    // socklen_t client_addr_len;

    // //Accept incomming communication
    // int client_fd = accept(_listener, &client_addr, &client_addr_len);

    // std::cout << "client_fd " << client_fd << std::endl;

    // if (client_fd == -1)
    // {
    //     return;
    // }

    int i = 0;

    std::string command = "";

    std::cout << "------------------------------------- " <<  std::endl;
    // for (;;)
    // {
        memset(&_buffer,0,256);
        //std::cout << "client_fd : " << client_fd << std::endl;
        res = recv(client_fd, _buffer, sizeof(_buffer), 0);
        std::cout << "res : " << res << std::endl;
        if (res == -1)
        {
            return;               /* Ignore failed request */
        }

        if (res == 0)
        {
            return;               /* Receive empty */
        }
        std::cout << "res : " << res << std::endl;
        std::cout << std::endl << "[Client->Server]" << this->_buffer << std::endl;

        command = this->parse(this->_buffer, client_fd);

        // temp value, to be replaced by a call to client
        std::string nickname = "vroch";

        if (command.find("CAP ",0) == 0)
        {
            this->Cmds_CAP(client_fd, nickname);
        }

        if (command.find("PING", 0) == 0)
        {
            this->Cmds_ping(client_fd);
        }

        if (command.find("NICK", 0) == 0)
        {

        }

        if (command.find("QUIT", 0) == 0)
        {

			// std::string nick = _fd_nick_list[client_fd];
			// delete(_clientList[nick]); //egalement clot le fd
			// _clientList.erase(nick);
            // _fd_nick_list.erase(client_fd);
            // //continue;
        }

        if (command.find("squit", 0) == 0)
        {
			// std::string nick = _fd_nick_list[client_fd];
			// delete(_clientList[nick]); //egalement clot le fd
			// _clientList.erase(nick);
            // _fd_nick_list.erase(client_fd);
            // // deconnecter le client
            // ;
        }

        i++;

    // }

    std::cout << "------------------------------------- " <<  std::endl;



}
