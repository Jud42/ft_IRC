#include "Server.hpp"



std::string	Server::parse(const std::string _buffer, const int newListener)
{
    std::string irc_cmd[3] = {"PASS", "NICK", "USER"};
    std::string segment[10];
    std::string nickname;
    std::string pass;
    std::string user;

    std::string message = _buffer;
    std::cout << BLU << "[PARSE] message : " << message << NOC << std::endl;
    unsigned int pos_start = 0;
    unsigned int pos_length = 0;
	if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -------------------------------
	{
			std::cout << BLU;
			print_all_caractere(message);
			std::cout << NOC;
	} // --------------------------------------------------------------------------------------

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

            if (segment[seg].find("JOIN", 0) == 0)
            {
                user = segment[seg].substr(5, segment[seg].size());
                std::cout << GRE << "[FEED Client] USER[" << user << "] : " << newListener << "|" << NOC << std::endl;
            }

            if (segment[seg].find("PART", 0) == 0)
            {
                user = segment[seg].substr(5, segment[seg].size());
                std::cout << GRE << "[FEED Client] USER[" << user << "] : " << newListener << "|" << NOC << std::endl;
            }


        }

        pos_start = 0;

        if (segment[seg] != "")
            seg += 1;

    }



    return segment[0];

}
