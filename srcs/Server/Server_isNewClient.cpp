#include "Server.hpp"

bool Server::isNewClient(int &client_fd, std::string buffer)
{
	std::cout << "fd: " << client_fd << " => [isNewClient] "
		<< buffer << std::endl;
	Client *temp = new Client(client_fd, buffer);
	std::string nick = temp->getNickname();

	if (temp->getPassword() != this->_pass && temp->getPassword() != "0")
	{
		std::string cap_response = "464 ERR_PASSWDMISMATCH Wrong password\r\n";
		send(client_fd, cap_response.c_str(), cap_response.length(), 0);
		std::cout << "Erreur d'authentification : mot de passe invalide " << temp->getPassword() << this->_pass << std::endl;
		delete temp;
		return (false);
	}
	if (nick.length() > 20 || (nick.length() < 3 && nick != "#" ))
	{
		std::string cap_response = "432 " + nick + "Nickname " + nick + " does not respond to standard \r\n";
		std::cout << client_fd << " [Server->Client]" << cap_response << std::endl;
		send(client_fd, cap_response.c_str(), cap_response.length(), 0);
		std::cout << "*" << nick << "*" << "Nickname does not respond to standard length: " << + nick.length() << std::endl;
		delete temp;
		return (false);
	}
	if (_clientList.count(nick) > 0)
	{
		if (temp->get_ip() != _clientList[temp->getNickname()]->get_ip() || temp->get_data() != _clientList[temp->getNickname()]->get_data())
		{
			std::string cap_response = "433 Nickname already exist, please choose another\r\n";
			send(client_fd, cap_response.c_str(), cap_response.length(), 0);
			std::cout << "Nickname already used" << std::endl;
		}
		delete temp;
		return (false);
	}
	this->_clientList.insert(std::pair<std::string, Client *>(temp->getNickname(), temp));
	this->_fd_nick_list.insert(std::pair<int, std::string>(client_fd, temp->getNickname()));
	this->printAddressIp(client_fd);
	std::cout << YEL << "nouveau client: " <<  std::endl;
	std::cout << "fd: " << (this->_clientList[_fd_nick_list[client_fd]])->getClientFd() << std::endl;
	std::cout << "nick: " << (this->_clientList[_fd_nick_list[client_fd]])->getNickname() << std::endl;
	std::cout << "password: " << (this->_clientList[_fd_nick_list[client_fd]])->getPassword() << std::endl;
	std::cout << "modes: " << (this->_clientList[_fd_nick_list[client_fd]])->getModes() << std::endl;
	std::cout << "user: " << (this->_clientList[_fd_nick_list[client_fd]])->get_user() << std::endl;
	std::cout << "ip(temp): " << (this->_clientList[_fd_nick_list[client_fd]])->get_ip()  << std::endl;
	std::cout << "realname: " << (this->_clientList[_fd_nick_list[client_fd]])->get_realname() << NOC << std::endl;
	std::cout << "----------------------------- " <<  std::endl;
	return(true);
}
