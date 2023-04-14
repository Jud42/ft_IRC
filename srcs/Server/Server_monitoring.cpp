#include "Server.hpp"

void Server::monitoring( void )
{
	int	event;
	struct pollfd server = {_listener, POLLIN, 0};
	_fds.push_back(server);

	while (true) {

		std::cout << "==av poll==" << std::endl;
		//take evenement
		event = poll(_fds.data(), _fds.size(), TIMEOUT);
		if (event < 0)
				throw std::runtime_error("[SERVER_MONITORING] - ERROR poll()");
<<<<<<< HEAD

		for (int i = 0; i < MAX_CLIENTS + 1; i++)
			std::cout << "_fds fd: " << _fds[i].fd << " revents: " << _fds[i].revents << std::endl;

		//check a new connexion
		if (_fds[0].revents & POLLIN)
		{
			std::cout << "je passe" << std::endl;
			if (_nb_clients == MAX_CLIENTS)
				break ;//manage max client

			socklen_t addrlen = sizeof(_addrclients[_nb_clients]);
			int client_fd = accept(_listener, &_addrclients[_nb_clients], &addrlen);
			if (client_fd == -1)
				throw std::runtime_error("[SERVER_MONITORING] - ERROR binding() failed");
			//if (!this->treatment_new(client_fd))
			//{
				_fds[_nb_clients + 1].fd = client_fd;
				_fds[_nb_clients + 1].events = POLLIN;
				_nb_clients++;
				_client_fd.push_back(client_fd);
				std::cout  << "client cree " << _fd_nick_list[client_fd] << std::endl;
			//}
			// memset(&_buffer,0,256);
			// recv(_fds[0].fd, _buffer, sizeof(_buffer), 0);
			std::cout << "buffer : " << _buffer << std::endl;
			continue;
		}

		std::cout << "buffer avant recv: " << _buffer << std::endl;

		//check event on fd_client if there are a data available
		for (int i = 1; i != _nb_clients + 1; i++) {

			if (_fds[i].revents == POLLIN) {
				std::cout << _fds[i].fd << std::endl;

			/****/
				memset(&_buffer,0,256);
				int res = recv(_fds[i].fd, _buffer, sizeof(_buffer), 0);
				std::cout << "res : " << res << std::endl;
				if (res < 0)
					throw std::runtime_error("[SERVER_MONITORING] - ERROR recv() failed");

				if (res == 0)
				{
					// supprimer le client et enlever la donner des 2 map
					std::cout << "deconnection du fd : " << _fds[i].fd << std::endl;
					close(_fds[i].fd);
					_fds[i].revents = -1;
					exit(0);

				}
				//std::cout << "res : " << res << std::endl;
				std::cout << _fds[i].fd << "[Client->Server]" << this->_buffer << std::endl;

				std::string command = this->parse(this->_buffer, _fds[i].fd);

				// temp value, to be replaced by a call to client
				// std::string nickname = "exo";

				if (command.find("CAP ",0) == 0)
				{
					this->Cmds_CAP(_fds[i].fd, _fd_nick_list[_fds[i].fd]);
=======
		std::cout << "==ap poll==" << std::endl;
		/**TEST PRINT FD**/
		std::vector< struct pollfd >::iterator it;
		for (it = _fds.begin(); it != _fds.end(); it++)
			std::cout << "_fds fd: " << it->fd << " revents: " << it->revents << std::endl;
		/*-----*/

		for (it = _fds.begin(); it != _fds.end(); it++) {
			//data in
			if (it->revents == POLLIN) {
				//incoming connection on server
				if (it->fd == _listener) {
					this->createConnexion(); //accept()
					break ;
>>>>>>> main
				}
				//data available on fd_clients
				else if (it->fd != _listener) {
					int flag = this->readFdClient(it->fd); 
					if (flag != SUCCESS_LOG) {//recv()
						this->logoutClient(it, flag);
						break ;
					}
					std::cout << "********CONNEXION******" << std::endl;
					this->printAddressIp(it->fd);
					std::cout << "***********************" << std::endl;
					continue ;
				}

<<<<<<< HEAD
				if (command.find("JOIN", 0) == 0)
				{
					this->Cmds_join(_fds[i].fd, command.substr(5), _fd_nick_list[_fds[i].fd]);
				}

				if (command.find("PART", 0) == 0)
				{
					this->Cmds_part(_fds[i].fd, command.substr(5), _fd_nick_list[_fds[i].fd]);
				}

				if (command.find("NICK", 0) == 0)
				{

				}

				if (command.find("QUIT", 0) == 0)
				{
					// deconnecter le client
					//continue;
					std::cout << "QUIT deconnection du fd : " << _fds[i].fd << std::endl;
					close(_fds[i].fd);
					_fds[i].revents = -1;
					exit(0);
				}

				if (command.find("squit", 0) == 0)
				{
					// deconnecter le client
					break;
				}
				std::cout << "------------------------------------- " <<  std::endl;
=======
>>>>>>> main
			}
			//else if (it->revents & POLLOUT) //le fd est pret pour l'ecriture
			else if (it->revents == POLLHUP || 
					it->revents == POLLIN + POLLHUP) {//logout client
																 
				std::cout << "fd: " << it->fd << " LOGOUT" << std::endl;
				this->logoutClient(it, LOGOUT);
				break ;
			}
			//else if (it->revents & POLLERR) //error on fd
		}

	}
}
