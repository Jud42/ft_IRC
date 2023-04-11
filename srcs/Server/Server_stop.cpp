#include "Server.hpp"

void	Server::stop(void)
{  
	
	freeaddrinfo(this->_addrs);

}