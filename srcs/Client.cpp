#include "Client.hpp"

Client::Client(){}

Client::Client(int client_fd, char *client_data)
: _modes("i"), _clientFd(client_fd)
{
	_canal.push_back("main");
    std::string message = client_data;
	std::cout << RED << "START PARSE" << std::endl;
    std::cout << BLU << "[PARSE] message : " << message << NOC << std::endl;
    unsigned int pos_start = 0;
    unsigned int pos_length = 0;

    std::string remains = "";

    int seg = 0;
	std::string irc_cmd[3] = {"PASS", "NICK", "USER"};
    std::string segment[10];

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
                std::cout << GRE << "[FEED Client] PASS[" << this->_password << "] : " << client_fd << "|" << NOC << std::endl;
            }

            if (segment[seg].find("NICK", 0) == 0)
            {
                this->_nickname = segment[seg].substr(5, segment[seg].size());
                std::cout << GRE << "[FEED Client] NICK[" << this->_nickname << "] : " << client_fd << "|" << NOC << std::endl;
            }

            if (segment[seg].find("USER", 0) == 0)
            {
                this->_username = segment[seg].substr(5, segment[seg].size());
                std::cout << GRE << "[FEED Client] USER[" << this->_username << "] : " << client_fd << "|" << NOC << std::endl;
            }

        }

        pos_start = 0;

        if (segment[seg] != "")
            seg += 1;
	}
}

Client::~Client()
{
	send(this->_clientFd, "Goodbye", 8, 0);

    // Fermer la connexion avec le serveur IRC
    close(this->_clientFd);

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
