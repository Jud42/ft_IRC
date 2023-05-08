// a faire gestion des channels: 1er channel


#include "Client.hpp"

Client::Client(){}

Client::Client(int client_fd, std::string client_data)
: _data("to_be_filled"), _nickname("#"),  _password("0"), _modes("i"), _clientFd(client_fd), _ip("0"), _clientInfo(0)
{
    std::string message = client_data;
	print_all_caractere(client_data);
	std::cout << RED << "START PARSE" << std::endl;
    std::cout << BLU << "[PARSE] message : " << message << NOC << std::endl;
    unsigned int pos_start = 0;
    unsigned int pos_length = 0;

	// _privMsgContactsFd.push_back(1000);

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

        if (segment[seg] != "")
        {
            // feed the client definition : to be added
            if (segment[seg].find("PASS", 0) == 0)
            {
				_clientInfo++;
                this->_password = segment[seg].substr(5, segment[seg].size());
                std::cout << GRE << "[FEED Client] PASS[" << this->_password << "] : " << client_fd << "|" << NOC << std::endl;
            }

            if (segment[seg].find("NICK", 0) == 0)
            {
				_clientInfo++;
                this->_nickname = segment[seg].substr(5, segment[seg].size());
                std::cout << GRE << "[FEED Client] NICK[" << this->_nickname << "] : " << client_fd << "|" << NOC << std::endl;
            }
			std::cout << "find user " << segment[seg].find("USER", 0) << std::endl;
            if (segment[seg].find("USER", 0) == 0)
            {
				_clientInfo++;
                this->_data = segment[seg].substr(5, segment[seg].size());
                std::cout << GRE << "[FEED Client] USER[" << this->_data << "] : " << client_fd << "|" << NOC << std::endl;
            }
			seg += 1;
        }
        pos_start = 0;
	}
	 std::cout << "client info: " << _clientInfo << std::endl;
	_username = _data.substr(_data.find(" ") + 1);
	_username = _username.substr(0, _username.find(" "));
	_realname = _data.substr(_data.find(":") + 1);

}

Client::Client(Client cpyClient, std::string newNickname)
	: _nickname(newNickname), _username(cpyClient._username), _password(cpyClient._password),
	_modes(cpyClient._modes), _clientFd(cpyClient._clientFd)
{
}

Client::~Client()
{
	std::cout << GRE << "destruction client" << NOC << std::endl;
	std::string cap_response = "*\r\n";
	std::cout << _clientFd << " [Server->Client]" << cap_response << std::endl;
	send(_clientFd, cap_response.c_str(), cap_response.length(), 0);

	std::vector<int>::iterator it = _privMsgContactsFd.begin();
	for( ; it != _privMsgContactsFd.end(); ++it)
	{
		std::string cap_response = ":" + _nickname + "!~" + _username + '@' + _ip + " QUIT\r\n";
		std::cout << *it << " [Server->Client]" << cap_response << std::endl;
		send(*it, cap_response.c_str(), cap_response.length(), 0);
	}

    // Fermer la connexion avec le serveur IRC
    // close(this->_clientFd);

}

void Client::setNickname(std::string newNick)
{
	this->_nickname = newNick;
}

const std::string &Client::getNickname() const
{
	return(this->_nickname);
}

void Client::setPassword(std::string pass)
{
	this->_password = pass;
}

const std::string &Client::getPassword() const
{
	return(this->_password);
}

void Client::setModes(std::string mode)
{
	this->_modes = mode;
}

const std::string &Client::getModes() const
{
	return(this->_modes);
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
	if (!findContactFd(contact_fd))
		_privMsgContactsFd.push_back(contact_fd);
}
void	Client::delContactFd(int contact_fd)
{
	std::vector<int>::iterator it = _privMsgContactsFd.begin();

	for( ; it !=_privMsgContactsFd.end(); ++it)
	{
		if (*it == contact_fd)
			_privMsgContactsFd.erase(it);
	}
}

const int &Client::getClientFd() const
{
	return(this->_clientFd);
}

std::vector<int>	Client::getContactsFd() const
{
	return (_privMsgContactsFd);
}

void Client::set_ip(std::string ip)
{
	_ip = ip;
}

const std::string &Client::get_ip() const
{
	return(_ip);
}

void Client::set_user(std::string user)
{
	_username = user;
}

const std::string &Client::get_user() const
{
	return(_username);
}

void Client::set_realname(std::string realname)
{
	_realname = realname;
}

const std::string &Client::get_realname() const
{
	return(_realname);
}

void Client::set_data(std::string data)
{
	_data = data;
}

const std::string &Client::get_data() const
{
	return(_data);
}

void	Client::set_clientInfo(int i)
{
	_clientInfo += i;
}

const int	&Client::get_clientInfo() const
{
	return (_clientInfo);
}


/*

client_data exemple:

CAP LS
NICK vhaefeli
USER vhaefeli vhaefeli c1r4s1.42lausanne.ch :Vanessa Haefeli

*/
