#include "Server.hpp"

bool Server::isNewClient(int &client_fd)
{
	std::cout << "fd: " << client_fd << " => [isNewClient] "
		<< this->_buffer << std::endl;
	Client *temp = new Client(client_fd, _buffer);
	// if (temp->getPassword() != this->_pass)
	// {
	// 	send(client_fd, "ERR_PASSWDMISMATCH", 19, 0);
	// 	std::cout << "Erreur d'authentification : mot de passe invalide" << temp->getPassword() << this->_pass << std::endl;
	// 	delete temp;
	// 	return (1);
	// }
	if (_clientList.count(temp->getNickname()) > 0)
	{
		std::string cap_response = "433 Nickname already exist, please choose another\r\n";
		send(client_fd, cap_response.c_str(), cap_response.length(), 0);
		std::cout << "Nickname already used" << std::endl;
		delete temp;
		return (false);
	}
	this->_clientList.insert(std::pair<std::string, Client *>(temp->getNickname(), temp));
	this->_fd_nick_list.insert(std::pair<int, std::string>(client_fd, temp->getNickname()));

	std::cout << RED << "nouveau client: " <<  std::endl;
	std::cout << "fd: " << (this->_clientList[_fd_nick_list[client_fd]])->getClientFd() << std::endl;
	std::cout << "nick: " << (this->_clientList[_fd_nick_list[client_fd]])->getNickname() << std::endl;
	std::cout << "password: " << (this->_clientList[_fd_nick_list[client_fd]])->getPassword() << std::endl;
	std::cout << "modes: " << (this->_clientList[_fd_nick_list[client_fd]])->getModes() << NOC << std::endl;

	std::cout << "----------------------------- " <<  std::endl;
	return(true);
}
