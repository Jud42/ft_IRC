#include "Server.hpp"
#include <vector>

void Server::monitoring( void )
{
	// Attendre une connexion entrante
    //struct sockaddr_in client_addr;
    //socklen_t client_addr_len = sizeof(client_addr);
    
	std::vector< pollfd * > fds;
	//struct pollfd pollserver = {_listener, POLLIN, 0};
	pollfd server = {_listener, POLLIN, 0};
	fds.push_back(&server);

	pollfd test;
	memset(&test, 0, sizeof(test));

	std::cout << test.fd << std::endl;

	while (true) {
	
		//wait evenement
		if (poll(*fds.data(), fds.size(), TIMEOUT) <= 0)
				throw std::runtime_error("[SERVER_MONITORING] - ERROR poll() failed: timeout");

		//iterate each fd for check event

		if (fds.front()->revents & POLLIN) {
		
			std::cout << "je passe" << std::endl;
			if (_nb_client == MAX_CLIENTS)
				;//manage max client 

			socklen_t addrlen = _addrs->ai_addrlen;
			int client_fd = accept(_listener, _addrs->ai_addr, &addrlen);
			if (client_fd == -1)
				throw std::runtime_error("[SERVER_MONITORING] - ERROR binding() failed");
					
			//add new fd_client in vector pollfd
			pollfd *pollclient = new pollfd;
			pollclient->fd = client_fd;
			pollclient->events = POLLIN;
			pollclient->revents = 0;
			fds.push_back(pollclient);
			_nb_client++;
			std::string a("welcome");
			send(client_fd, &a, a.size(), 0);
			continue ;

		}

		std::vector< pollfd * >::iterator it = fds.begin(); 
		std::vector< pollfd * >::iterator it_end = fds.end(); 
		for (it += 1; it != it_end; it++) {

			if ((*it)->revents == POLLIN)	
				std::cout << "receeive" << std::endl;
		}
	}

	//close(_listener);
	//close() //all fd_client
}
