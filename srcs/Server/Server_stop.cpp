#include "Server.hpp"

void	Server::stop(void)
{
	if (this->_addrs)
	{
		freeaddrinfo (_addrs);
		_addrs = NULL;
	}

}