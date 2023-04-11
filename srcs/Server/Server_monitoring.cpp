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

		std::vector< pollfd * >::iterator it; 
		std::vector< pollfd * >::iterator it_end = fds.end(); 
		for (it = fds.begin(); it != it_end; it++) {

			if ((*it)->revents == POLLIN)	
				std::cout << "receeive" << std::endl;
		}
	}

	//close(_listener);
	//close() //all fd_client
}
	struct pollfd ev[200];
	memset (ev, 0, sizeof(ev));
	ev[0].events = POLLIN;
	ev[0].fd = _listener;
	int nfds = 1;
	
	// upadate the epoll instance with the new epoll 
	// EPOLL_CTL_ADD = Add an entry to the interest list of the epoll file
	//int res = epoll_ctl (_efd, EPOLL_CTL_ADD, _listener, &ev);


	int res = poll(ev, nfds, TIMEOUT);

	if ("DEBUG" ==_IRCconfig->getConfigValue("DEBUG")) // -------------------------------------
	{
		std::cout << BLU;		
		std::cout << "[SERVER_MONITORING] DEBUG - Provide poll value" << std::endl;
		std::cout << " res <" << res << ">" << std::endl;
		std::cout << " ev.events <" << ev->events << ">" << std::endl;
		std::cout << " ev.fd <" << ev->fd << ">" << std::endl;
		std::cout << " ev.revents <" << ev->revents << ">" << std::endl;
		std::cout << " nfds <" << nfds << ">" << std::endl;
		std::cout << NOC;
	} // ---------------------------------------------------------------------------------------	
	if (res < 0)
		throw std::runtime_error("[SERVER_MONITORING]- ERROR poll failed");
	//if (res == 0)
	//	throw std::runtime_error("[SERVER_MONITORING]- ERROR poll timed out");		

	


}
