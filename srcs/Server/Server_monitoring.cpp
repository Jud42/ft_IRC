#include "Server.hpp"

void Server::monitoring( void )
{
	// poll_create a new poll instance.
	// _efd = epoll_create1 (0);


	//if (_efd < 0)
	//	throw std::runtime_error("[SERVER_MONITORING]- ERROR epoll_create1 failed");

	// add listener to efd. Watch the event Epollin 
	// int nfds  = 1;
	
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