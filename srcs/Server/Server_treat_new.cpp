#include "Server.hpp"

int Server::treatment_new(int client_fd)
{
    int res = 0;

    std::string command = "";

    std::cout << "creation client fd " << client_fd << std::endl;
	memset(&_buffer,0,256);
	//std::cout << "client_fd : " << client_fd << std::endl;
	res = recv(client_fd, _buffer, sizeof(_buffer), 0);
	std::cout << "res : " << res << std::endl;
	if (res == -1)
	{
		for (int i(0); i < 3 && res == -1; i++)
		{
			std::cout << "retry "<< std::endl;
			res = recv(client_fd, _buffer, sizeof(_buffer), 0);
			std::cout << "res : " << res << std::endl;
		}
		if (res == -1)
		{
			close(client_fd);
			return(1);               /* Ignore failed request */
		}
	}

	if (res == 0)
	{
		std::cout << RED << "deconnection du fd : " << client_fd << NOC << std::endl;
		close(client_fd);
		return(1);               /* Receive empty */
	}
	std::cout << "res : " << res << std::endl;
	std::cout << std::endl << "[Client->Server]" << this->_buffer << std::endl;
	Client *temp = new Client(client_fd, _buffer);
	if (temp->getPassword() != this->_pass)
	{
		send(client_fd, "ERR_PASSWDMISMATCH", 19, 0);
		std::cout << "Erreur d'authentification : mot de passe invalide: recu: " << temp->getPassword() << "attendu: " << this->_pass << std::endl;
		close(client_fd);
		delete temp;
		return (1);
	}
	if (_clientList.count(temp->getNickname()) > 0)
	{
		send(client_fd, "ERR_NICKNAMEINUSE", 18, 0);
		std::cout << "Nickname already used" << std::endl;
		close(client_fd);
		delete temp;
		return (1);
	}
	_clientList[temp->getNickname()] = *temp;
	_fd_nick_list[client_fd] = temp->getNickname();

    std::cout << "------------------------------------- " <<  std::endl;
	return(0);

}
