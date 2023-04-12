#include "Server.hpp"
#include <vector>

void Server::monitoring( void )
{
	struct pollfd server = {_listener, POLLIN, 0};
	_fds[_nb_client] = server;
	
	int	retpoll = -1;

	while (true) {
	
		//wait evenement
		retpoll = poll(_fds, _nb_client + 1, TIMEOUT);
		if (retpoll == 0)
				throw std::runtime_error("[SERVER_MONITORING] - poll() timeout");
		else if (retpoll < 1)
				throw std::runtime_error("[SERVER_MONITORING] - ERROR poll()");

		for (int i = 0; i < MAX_CLIENTS + 1; i++)
			std::cout << "_fds fd: " << _fds[i].fd << " revents: " << _fds[i].revents << std::endl;

		//check a new connexion
		if (_fds[0].revents & POLLIN) {
		
			std::cout << "je passe" << std::endl;
			if (_nb_client == MAX_CLIENTS)
				break ;//manage max client 

			socklen_t addrlen = _addrs->ai_addrlen;
			int client_fd = accept(_listener, _addrs->ai_addr, &addrlen);
			if (client_fd == -1)
				throw std::runtime_error("[SERVER_MONITORING] - ERROR binding() failed");
			//add new fd_client in vector pollfd
			//pollfd *pollclient = new pollfd;
			_fds[_nb_client + 1].fd = client_fd;
			_fds[_nb_client + 1].events = POLLIN;
			_nb_client++;
			_client_fd.push_back(client_fd);
			continue ;
		}

		for (int i = 1; i != _nb_client + 1; i++) {

			if (_fds[i].revents == POLLIN) {	
				std::cout << _fds[i].fd << std::endl;

			/****/
				int res = 1;

				memset(&_buffer,0,256);
				res = recv(_fds[i].fd, _buffer, sizeof(_buffer), 0);
				//std::cout << "res : " << res << std::endl;
				if (res < 0)
					throw std::runtime_error("[SERVER_MONITORING] - ERROR recv() failed");

				//std::cout << "res : " << res << std::endl;
				std::cout << _fds[i].fd << "[Client->Server]" << this->_buffer << std::endl;

				std::string command = this->parse(this->_buffer, _fds[i].fd);

				// temp value, to be replaced by a call to client
				std::string nickname = "exo";

				if (command.find("CAP ",0) == 0)
				{
					this->Cmds_CAP(_fds[i].fd, nickname);
				}

				if (command.find("PING", 0) == 0)
				{
					this->Cmds_ping(_fds[i].fd);
				}

				if (command.find("NICK", 0) == 0)
				{

				}

				if (command.find("QUIT", 0) == 0)
				{
					// deconnecter le client
					//continue;
				}

				if (command.find("squit", 0) == 0)
				{
					// deconnecter le client
					break;
				}
				std::cout << "------------------------------------- " <<  std::endl;
			}
		}

			/****/
	}

//	close(_listener);
//	close() //all fd_client
}
