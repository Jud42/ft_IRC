#include "Server.hpp"

void Server::monitoring( void )
{
	// epoll_create creates a new epoll instance.
	_efd = epoll_create1 (0);
	if ("DEBUG" ==_IRCconfig->getConfigValue("DEBUG")) // -------------------------------------
	{
		std::cout << BLU;		
		std::cout << "[SERVER_MONITORING] DEBUG - Provide epoll_create value" << std::endl;
		std::cout << " _efd <" << _efd << ">" << std::endl;
		std::cout << NOC;
	} // ---------------------------------------------------------------------------------------

	if (_efd < 0)
		throw std::runtime_error("[SERVER_MONITORING]- ERROR epoll_create1 failed");

	// add listener to efd. Watch the event Epollin 
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = _listener;
	// upadate the epoll instance with the new epoll 
	// EPOLL_CTL_ADD = Add an entry to the interest list of the epoll file
	int res = epoll_ctl (_efd, EPOLL_CTL_ADD, _listener, &ev);
	if (res < 0)
		throw std::runtime_error("[SERVER_MONITORING]- ERROR epoll_ctl listener add failed");
}