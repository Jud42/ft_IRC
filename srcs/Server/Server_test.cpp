#include "Server.hpp"

void Server::test(void)
{
    std::cout <<BLU << "TEST" << NOC <<std::endl;

    int res = 0;

    struct sockaddr client_addr;
    socklen_t client_addr_len;
    
    res = recv(_listener, _buffer, sizeof(_buffer), 0);
    std::cout << "Buffer : " <<  _buffer << std::endl;
 
    

    //Accept incomming communication
    int newListener = accept(_listener, &client_addr, &client_addr_len);

    std::cout << "NewListener " << newListener << std::endl;

    int i = 0;
    int snd;

    std::string cap_response = "CAP * ACK";
    snd = send(newListener, cap_response.c_str(), cap_response.length(), 0);


    std::cout << "------------------------------------- " <<  std::endl;
    for (;;)
    {

        res = recv(newListener, _buffer, sizeof(_buffer), 0);  

        if (res == -1)
            continue;               /* Ignore failed request */
        
        
        this->parse(_buffer);
        std::string message = _buffer;
        unsigned int pos_length = message.find("\r\n", 0);
        std::string command = message.substr(0, pos_length);

        std::string nickname = "vroch";

        std::cout << command << std::endl;

        if (command == "CAP END" || command == "CAP LS")
        {
            std::cout << " CASE CAP END" << std::endl;
            std::string cap_response = nickname + ":Welcome to the server, " + nickname + "!\r\n";
            snd = send(newListener, cap_response.c_str(), cap_response.length(), 0);
            std::cout << " send response:<" << cap_response << ">" << std::endl;
            std::cout << " send :<" << snd << ">" << std::endl;
        }

        i++;

    }

    std::cout << "------------------------------------- " <<  std::endl;


}
