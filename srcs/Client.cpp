// a faire gestion des channels: 1er channel


#include "Client.hpp"

Client::Client(){}

Client::Client(int client_fd, char *client_data)
: _data("to_be_filled"), _nickname("#"),  _password("0"), _modes("i"), _clientFd(client_fd), _ip("0")
{

    std::string message = client_data;
	std::cout << RED << "START PARSE" << std::endl;
    std::cout << BLU << "[PARSE] message : " << message << NOC << std::endl;
    unsigned int pos_start = 0;
    unsigned int pos_length = 0;

	_channel.push_back("0");
	_privMsgContactsFd.push_back(1000);

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
        pos_start = 0;

        if (segment[seg] != "")
            seg += 1;
	}
	_username = _data.substr(_data.find(" ") + 1);
	_username = _username.substr(0, _username.find(" "));
	_realname = _data.substr(_data.find(":") + 1);
}

Client::Client(Client cpyClient, std::string newNickname)
	: _nickname(newNickname), _username(cpyClient._username), _password(cpyClient._password),
	_modes(cpyClient._modes), _channel(cpyClient._channel), _clientFd(cpyClient._clientFd)
{
}

Client::~Client()
{
	std::cout << GRE << "destruction client" << NOC << std::endl;
	std::string cap_response = "BYE\r\n";
	std::cout << _clientFd << " [Server->Client]" << cap_response << std::endl;
	send(_clientFd, cap_response.c_str(), cap_response.length(), 0);

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

void Client::setPassword(std::string pass)
{
	this->_password = pass;
}

std::string Client::getPassword()
{
	return(this->_password);
}

void Client::setModes(std::string mode)
{
	this->_modes = mode;
}

std::string Client::getModes()
{
	return(this->_modes);
}

bool	Client::findChannel(std::string channel_name)
{
	std::vector<std::string>::iterator it = _channel.begin();;

	for( ; it !=_channel.end(); ++it)
	{
		if (*it == channel_name)
			return (true);
	}
	return (false);
}

std::vector<std::string>	Client::getChannel()
{
	std::vector<std::string>::iterator it = _channel.begin();

	// print all channel but return the vector
	for( ; it !=_channel.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
	return (this->_channel);
}

void	Client::removeChannel(std::string channel)
{
	std::vector<std::string>::iterator it = _channel.begin();;

	for( ; it !=_channel.end(); ++it)
	{
		if (*it == channel)
			_channel.erase(it);
	}
}

void	Client::addChannel(std::string channel)
{
	_channel.push_back(channel);
}

bool	Client::findContactFd(int contact_fd)
{
	std::vector<int>::iterator it = _privMsgContactsFd.begin();;

	for( ; it !=_privMsgContactsFd.end(); ++it)
	{
		if (*it == contact_fd)
			return (true);
	}
	return (false);
}
void	Client::addContactFd(int contact_fd)
{
	_privMsgContactsFd.push_back(contact_fd);
}
void	Client::delContactFd(int contact_fd)
{
	std::vector<int>::iterator it = _privMsgContactsFd.begin();;

	for( ; it !=_privMsgContactsFd.end(); ++it)
	{
		if (*it == contact_fd)
			_privMsgContactsFd.erase(it);
	}
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

void Client::set_user(std::string user)
{
	_username = user;
}

std::string Client::get_user()
{
	return(_username);
}

void Client::set_realname(std::string realname)
{
	_realname = realname;
}

std::string Client::get_realname()
{
	return(_realname);
}

void Client::set_data(std::string data)
{
	_data = data;
}

std::string Client::get_data()
{
	return(_data);
}
/*

client_data exemple:

CAP LS
NICK vhaefeli
USER vhaefeli vhaefeli c1r4s1.42lausanne.ch :Vanessa Haefeli

*/
