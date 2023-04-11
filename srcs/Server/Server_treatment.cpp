#include "Server.hpp"

void Server::treatment(void)
{
    int res = 0;

    struct sockaddr client_addr;
    socklen_t client_addr_len;

    //Accept incomming communication
    int newListener = accept(_listener, &client_addr, &client_addr_len);

    std::cout << "NewListener " << newListener << std::endl;

    if (newListener == -1)
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
        res = recv(newListener, _buffer, sizeof(_buffer), 0);  
        //std::cout << "res : " << res << std::endl;
        if (res == -1)
        {
            continue;               /* Ignore failed request */
        }

        if (res == 0)
        {
            continue;               /* Receive empty */
        }
        std::cout << "res : " << res << std::endl;
        std::cout << std::endl << "[Client->Server]" << this->_buffer << std::endl;            
        
        command = this->parse(this->_buffer, newListener);
        
        // temp value, to be replaced by a call to client
        std::string nickname = "exo";

        if (command.find("CAP ",0) == 0)
        {
            this->Cmds_CAP(newListener, nickname);
        }

        if (command.find("PING", 0) == 0)
        {
            this->Cmds_ping(newListener);
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
