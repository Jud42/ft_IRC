#include "Server.hpp"

void Server::monitoring( void )
{
	int	event;
	struct pollfd server = {_listener, POLLIN, 0};
	_fds.push_back(server);
	int activity = SUCCESS_LOG;

	while (activity != LOGOUT_SERVER) {

		std::cout << "==av poll==" << std::endl;

		//take evenement
		event = poll(_fds.data(), _fds.size(), TIMEOUT);
		if (event < 0)
				throw std::runtime_error("[SERVER_MONITORING] - ERROR poll()");
		std::cout << "==ap poll==" << std::endl;
		/**TEST PRINT FD**/
		std::vector< struct pollfd >::iterator it;
		for (it = _fds.begin(); it != _fds.end(); it++)
			std::cout << "_fds fd: " << it->fd << " revents: " << it->revents << " POLLIN: " << POLLIN << " POLLHUP  " << POLLHUP << std::endl;
		/*-----*/

		for (it = _fds.begin(); it != _fds.end(); it++)
		{
			//data in
			if (it->revents == POLLIN) {
				//incoming connection on server
				if (it->fd == _listener) {
					this->createConnexion(); //accept()
					break ;
				}
				//data available on fd_clients
				else if (it->fd != _listener) {
					std::cout << "********CONNEXION******" << std::endl;
					std::cout << it->fd << std::endl;
					std::cout << "***********************" << std::endl;
					std::cout << "fd != _listener:_fds fd: " << it->fd << " revents: " << it->revents << " POLLIN: " << POLLIN << " POLLHUP  " << POLLHUP << std::endl;
					activity = this->readFdClient(it->fd);
					if (activity != SUCCESS_LOG) {//recv()
						this->logoutClient(it, activity);
						break ;
					}

					continue ;
				}

			}
			else if (it->revents == POLLHUP ||
					it->revents == POLLIN + POLLHUP) {//logout client

				std::cout << "Monitoring 51 fd: " << it->fd << " LOGOUT" << std::endl;
				this->logoutClient(it, LOGOUT);
				break ;
			}
			else if (it->revents == 32)
				_fds.erase(it);
		}
	}
}
