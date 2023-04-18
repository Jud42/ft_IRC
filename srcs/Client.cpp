// a faire gestion des channels: 1er channel


#include "Client.hpp"

Client::Client(){}

Client::Client(int client_fd, char *client_data)
: _modes("i"), _clientFd(client_fd), _ip("0")
{
	// _channel.push_back("main");
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
                this->_data = segment[seg].substr(5, segment[seg].size());
                std::cout << GRE << "[FEED Client] USER[" << this->_data << "] : " << client_fd << "|" << NOC << std::endl;
            }

        }

		_username = _data.substr(_data.find(" ") + 1);
		_username = _username.substr(0, _username.find(" "));
		_realname = _data.substr(_data.find(":") + 1);
        pos_start = 0;

        if (segment[seg] != "")
            seg += 1;

	}
}

Client::Client(Client cpyClient, std::string newNickname)
	: _nickname(newNickname), _username(cpyClient._username), _password(cpyClient._password),
	_modes(cpyClient._modes), _channel(cpyClient._channel), _clientFd(cpyClient._clientFd)
{
}

Client::~Client()
{
	std::cout << GRE << "destruction client" << NOC << std::endl;
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

bool	Client::findChannel(std::string channel_name)
{
	std::vector<Channel>::iterator it;

	for(it = _channel.begin(); it !=_channel.end(); ++it)
	{
		if (it->getChannelName() == channel_name)
			return (true);
	}
	return (false);
}

std::vector<Channel>	Client::getChannel()
{
	std::vector<Channel>::iterator it;

	// print all channel but return the vector
	for(it = _channel.begin(); it !=_channel.end(); ++it)
	{
		std::cout << it->getChannelName() << std::endl;
	}
	return (this->_channel);
}

void	Client::addChannel(Channel channel)
{
	_channel.push_back(channel);
}

int Client::getClientFd()
{
	return(this->_clientFd);
}

void Client::set_ip(std::string ip)
{
	_ip = ip;
}

std::string Client::get_ip()
{
	return(_ip);
}
std::string Client::get_user()
{
	return(_username);
}

std::string Client::get_realname()
{
	return(_realname);
}

/*

client_data exemple:

CAP LS
NICK vhaefeli
USER vhaefeli vhaefeli c1r4s1.42lausanne.ch :Vanessa Haefeli

*/
