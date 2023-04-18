#include "Server.hpp"

void	Server::stop(void)
{  
	this->logoutServer();
	//freeaddrinfo(this->_addrs);
}
