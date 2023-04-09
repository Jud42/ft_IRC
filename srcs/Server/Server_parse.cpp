#include "Server.hpp"



std::string	Server::parse(const std::string _buffer)
{
    std::string irc_cmd[3] = {"PASS", "NICK", "USER"};
    std::string segment[10];

    std::string message = _buffer;
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

        pos_start = 0;

        if (segment[seg] != "")
            seg += 1;

    }

    

    return segment[0];

}