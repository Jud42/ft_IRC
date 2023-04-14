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
		send(client_fd, "ERR_NICKNAMEINUSE", 18, 0);
		std::cout << "Nickname already used" << std::endl;
		delete temp;
		return (false);
	}
	_clientList[temp->getNickname()] = *temp;
	_fd_nick_list[client_fd] = temp->getNickname();

	std::cout << "----------------------------- " <<  std::endl;
	return(true);
}
