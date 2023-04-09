#include "Server.hpp"

void Server::test(void)
{
    std::cout <<BLU << "TEST" << NOC <<std::endl;

    int res = 0;

    struct sockaddr client_addr;
    socklen_t client_addr_len;
    
    //res = recv(_listener, _buffer, sizeof(_buffer), 0);
    //std::cout << std::endl << "[Client->Server]" << this->_buffer << std::endl;
    
 
    

    //Accept incomming communication
    int newListener = accept(_listener, &client_addr, &client_addr_len);

    std::cout << "NewListener " << newListener << std::endl;

    int i = 0;
    int snd;

    //std::string cap_response = "CAP * ACK";
    //snd = send(newListener, cap_response.c_str(), cap_response.length(), 0);
    std::string command = "";

    std::cout << "------------------------------------- " <<  std::endl;
    for (;;)
    {

        memset(&_buffer,0,256);
        res = recv(newListener, _buffer, sizeof(_buffer), 0);  
        if (res == -1)
            continue;               /* Ignore failed request */
        
        if (res == 0)
            continue;               /* Receive empty */

        std::cout << std::endl << "[Client->Server]" << this->_buffer << std::endl;            
        
        command = this->parse(_buffer);
        
        std::string nickname = "vroch";
        //std::string command = "CAP END";

        if (command == "CAP END" || command == "CAP LS")
        {
            //std::cout << " CASE CAP END" << std::endl;
            std::string cap_response = "001 " + nickname + " :Welcome to the server, " + nickname + "!\r\n";
            std::cout << "[Server->Client]" << cap_response << std::endl;
            snd = send(newListener, cap_response.c_str(), cap_response.length(), 0);
            cap_response = "MODE exo +i\r\n";
            std::cout << "[Server->Client]" << cap_response << std::endl;
            snd = send(newListener, cap_response.c_str(), cap_response.length(), 0);
            //std::cout << " send response:<" << cap_response << ">" << std::endl;
            std::cout << " send :<" << snd << ">" << std::endl;
        }

        if (command.find("PING", 0) == 0)
        {
            //std::cout << " CASE CAP END" << std::endl;
            std::string cap_response = "PONG exo-debian 127.0.0.1\r\n";
            std::cout << "[Server->Client]" << cap_response << std::endl;
            snd = send(newListener, cap_response.c_str(), cap_response.length(), 0);
            //std::cout << " send response:<" << cap_response << ">" << std::endl;
            std::cout << " send :<" << snd << ">" << std::endl;
        }

        if (command.find("WHOIS", 0) == 0)
        {
            //std::cout << " CASE CAP END" << std::endl;
            std::string cap_response = "PONG exo-debian 127.0.0.1\r\n";
            std::cout << "[Server->Client]" << cap_response << std::endl;
            snd = send(newListener, cap_response.c_str(), cap_response.length(), 0);
            //std::cout << " send response:<" << cap_response << ">" << std::endl;
            std::cout << " send :<" << snd << ">" << std::endl;
        }       

        if (command.find("QUIT", 0) == 0)
        {


        }   

        i++;

    }

    std::cout << "------------------------------------- " <<  std::endl;


}
