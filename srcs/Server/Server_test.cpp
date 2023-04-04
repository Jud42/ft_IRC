#include "Server.hpp"

void Server::test(void)
{
        std::cout << "TEST"   << std::endl;

    int res = 0;

    struct sockaddr_storage peer_addr;
    socklen_t peer_addr_len;
    int s;


    
    //for (;;) 
    
    //{

        peer_addr_len = sizeof(peer_addr);
        //res = recv(ev[i].fd, _buffer, sizeof(BUFFER_SIZE), 0);
        res = recvfrom(_listener, _buffer, BUFFER_SIZE, 0,
                       (struct sockaddr *) &peer_addr, &peer_addr_len);      
        //std::cout << " res <" << res << ">" << std::endl;

        if (res == -1)
            //continue;               /* Ignore failed request */
        
        if ("DEBUG" ==_IRCconfig->getConfigValue("DEBUG")) // -------------------------------------
        {
            std::cout << BLU;		
            std::cout << "[SERVER_TEST] DEBUG - recv value" << std::endl;
            std::cout << " res <" << res << ">" << std::endl;
            std::cout << _buffer << std::endl;
            std::cout << NOC;
        } // ---------------------------------------------------------------------------------------	
            char host[NI_MAXHOST], service[NI_MAXSERV];

            s = getnameinfo((struct sockaddr *) &peer_addr,
                               peer_addr_len, host, NI_MAXHOST,
                               service, NI_MAXSERV, NI_NUMERICSERV);
            if (s == 0)
            {
                printf("Received %d bytes from %s:%s\n",
                        res, host, service);

            }
                
        sleep(500000);


    //}

    

}