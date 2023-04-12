#include "Server.hpp"

void Server::treatment(int client_fd)
{
    int res = 0;

    //struct sockaddr client_addr;
    //socklen_t client_addr_len;

    //Accept incomming communication
<<<<<<< HEAD
	int NewListener = 0;
=======
    //int newListener = accept(_listener, &client_addr, &client_addr_len);
>>>>>>> d405eb7a2afdd478bd2e4842f7050b7f9d7721d8

    //std::cout << "NewListener " << newListener << std::endl;
    

    if (client_fd == -1)
    {
        return;
    }

    int i = 0;

    std::string command = "";

    std::cout << "------------------------------------- " <<  std::endl;
    for (;;)
    {

        memset(&_buffer,0,256);
        //std::cout << "newListener : " << newListener << std::endl;
        res = recv(client_fd, _buffer, sizeof(_buffer), 0);  
        //std::cout << "res : " << res << std::endl;
        if (res == -1)
        {
            continue;               /* Ignore failed request */
        }

        if (res == 0)
        {
            break;               /* Receive empty */
        }
        std::cout << "res : " << res << std::endl;
        std::cout << std::endl << client_fd << "[Client->Server]" << this->_buffer << std::endl;            
        
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
            // deconnecter le client
            //continue;
            break;
        }   

        if (command.find("squit", 0) == 0)
        {
            // deconnecter le client
            break;
        } 

        i++;

    }

    std::cout << "------------------------------------- " <<  std::endl;

    

}
