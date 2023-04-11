#include "Client.hpp"

Client::Client(int client_fd, std::string client_data)
: _modes(i), _canal(main), _clientFd(client_fd)
{













	std::string segment[10];
    std::string nickname;
    std::string pass;
    std::string user;

    std::string message = client_data;
	std::cout << RED << "START PARSE" << std::endl;
    std::cout << BLU << "[PARSE] message : " << message << NOC << std::endl;
    unsigned int pos_start = 0;
    unsigned int pos_length = 0;

    std::string remains = "";

    int seg = 0;

    while(remains != message)
    {

        pos_length = message.find("\r\n", pos_start);

        pos_length += 2;

        segment[seg] = message.substr(pos_start, pos_length - 2);
        remains = message.substr(pos_length, message.size());
        message = remains;
        remains = "";

        std::cout << GRE << "[PARSE] segment[" << seg << "] : " << segment[seg] << "|" << NOC << std::endl;

        if (seg != 0)
        {
            // feed the client definition : to be added
            if (segment[seg].find("PASS", 0) == 0)
            {
                pass = segment[seg].substr(5, segment[seg].size());
                std::cout << GRE << "[FEED Client] PASS[" << pass << "] : " << newListener << "|" << NOC << std::endl;
            }

            if (segment[seg].find("NICK", 0) == 0)
            {
                nickname = segment[seg].substr(5, segment[seg].size());
                std::cout << GRE << "[FEED Client] NICK[" << nickname << "] : " << newListener << "|" << NOC << std::endl;
            }

            if (segment[seg].find("USER", 0) == 0)
            {
                user = segment[seg].substr(5, segment[seg].size());
                std::cout << GRE << "[FEED Client] USER[" << user << "] : " << newListener << "|" << NOC << std::endl;
            }

        }

}

Client::~Client()
{
}

/*

client_data exemple:

CAP LS
NICK vhaefeli
USER vhaefeli vhaefeli c1r4s1.42lausanne.ch :Vanessa Haefeli

*/
