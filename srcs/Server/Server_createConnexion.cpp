#include "Server.hpp"

void Server::createConnexion( void ) {

	struct sockaddr addrclient;
	socklen_t addrlen = sizeof(addrclient);
	int client_fd = accept(_listener, &addrclient, &addrlen);
	if (client_fd == -1)
		throw std::runtime_error("[SERVER_MONITORING] - Error: accept()");

	//if (this->isNewClient(client_fd) == true) {
	if (_fds.size() - 1 != MAX_CLIENTS) {

		int flags = fcntl(client_fd, F_GETFL, 0);
		fcntl(client_fd, F_SETFL, flags | O_NONBLOCK);
		struct pollfd client = {client_fd, POLLIN, -1};
		_fds.push_back(client);
		_addrclient.insert(std::pair<int, sockaddr>(client_fd, addrclient));
		std::cout << "[createConnexion] ok => total client: " 
			<< _fds.size() - 1 << " => total address: " 
			<< _addrclient.size() <<std::endl;
	}
}
