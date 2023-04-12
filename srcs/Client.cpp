#include "Client.hpp"

Client::Client(int client_fd, std::string client_data)
: _modes(i), _canal(main), _clientFd(client_fd)
{

    std::string message = _buffer;
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
                this->_password = segment[seg].substr(5, segment[seg].size());
                std::cout << GRE << "[FEED Client] PASS[" << pass << "] : " << newListener << "|" << NOC << std::endl;
            }

            if (segment[seg].find("NICK", 0) == 0)
            {
                this->_nickname = segment[seg].substr(5, segment[seg].size());
                std::cout << GRE << "[FEED Client] NICK[" << nickname << "] : " << newListener << "|" << NOC << std::endl;
            }

            if (segment[seg].find("USER", 0) == 0)
            {
                this->_username = segment[seg].substr(5, segment[seg].size());
                std::cout << GRE << "[FEED Client] USER[" << user << "] : " << newListener << "|" << NOC << std::endl;
            }

        }

        pos_start = 0;

        if (segment[seg] != "")
            seg += 1;
}

Client::~Client()
{
	send(client_fd, "Goodbye", 8, 0);

    // Fermer la connexion avec le serveur IRC
    close(client_fd);

}

void Client::setNickname(std::string newNick)
{
	this->_nickname = newNick;
}

std::string Client::getNickname()
{
	return(this->_nickname);
}

std::string Client::getPassword()
{
	return(this->_password);
}

std::string Client::getModes()
{
	return(this->_modes);
}

std::vector<std::string> Client::getCanal()
{
	return(this->_canal);
}

int Client::getClientFd()
{
	return(this->_clientFd);
}



/*

client_data exemple:

CAP LS
NICK vhaefeli
USER vhaefeli vhaefeli c1r4s1.42lausanne.ch :Vanessa Haefeli

*/
