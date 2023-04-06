#include "Server.hpp"

void Server::test(void)
{
    std::cout << "TEST"   << std::endl;

    int res = 0;

    struct sockaddr client_addr;
    socklen_t client_addr_len;

    //int s;


    res = recv(_listener, _buffer, sizeof(_buffer), 0);
        //res = recvfrom(_listener, _buffer, BUFFER_SIZE, 0,
        //               (struct sockaddr *) &peer_addr, &peer_addr_len);


    //Accept incomming communication
    int newListener = accept(_listener, &client_addr, &client_addr_len);

    std::cout << "NewListener" << newListener << std::endl;



    for (;;)
    {

        res = recv(newListener, _buffer, sizeof(_buffer), 0);
        //res = recvfrom(_listener, _buffer, BUFFER_SIZE, 0,
        //               (struct sockaddr *) &peer_addr, &peer_addr_len);




        if (res == -1)
            continue;               /* Ignore failed request */

        if ("DEBUG" ==_IRCconfig->getConfigValue("DEBUG")) // -------------------------------------
        {
            std::cout << BLU;
            std::cout << "[SERVER_TEST] DEBUG - recv value" << std::endl;
            std::cout << " res <" << res << ">" << std::endl;
            std::cout << " Buffer <" << _buffer << ">" << std::endl;
            std::cout << NOC;
        } // ---------------------------------------------------------------------------------------
            //char host[NI_MAXHOST], service[NI_MAXSERV];



        std::string cap_response = "CAP * ACK :example.com/multi-prefix";
        int snd = send(newListener, cap_response.c_str(), cap_response.length(), 0);
        std::cout << " send response:<" << cap_response << ">" << std::endl;
        std::cout << " send :<" << snd << ">" << std::endl;


        std::string nickname = "vroch";
        cap_response = "Welcome to the server, " + nickname + "!\r\n";
        snd = send(newListener, cap_response.c_str(), cap_response.length(), 0);
        std::cout << " send response:<" << cap_response << ">" << std::endl;
        std::cout << " send :<" << snd << ">" << std::endl;


    }



}
