#include "Server.hpp"

void Server::listening(void)
{
	// review the list of address structures returned by getaddrinfo.
    // stop when the the socket and bind calls are successful. 

    
    int  optval = 1; // required by setsockopt : std value
	struct addrinfo *rptr;
	// pass over all addresse, next is proving the next refernece
	for (rptr = _addrs; rptr != NULL; rptr = rptr->ai_next) 
    {
        // creates an endpoint for communication and returns a descriptor.
		// The socket has the indicated type, which specifies the communication semantics. 
		_listener = socket (rptr->ai_family, rptr->ai_socktype, rptr->ai_protocol);

		if ("DEBUG" ==_IRCconfig->getConfigValue("DEBUG")) // -------------------------------------
		{
			std::cout << BLU;
			std::cout << "[SERVER_LISTENING] - DEBUG Socket result <" << _listener << ">" << std::endl;
			std::cout << NOC;
		} // --------------------------------------------------------------------------------------

		// establish if _listerner is not valid, then pass to the next one
		if (_listener == -1)
		{
			continue;
		}

		// configure socket
		// SOL_SOCKET for all sockets
		// SO_REUSEADDR indicates that the rules used in validating addresses supplied in 
		// a bind(2) call should allow reuse of local addresses. 
		int res = setsockopt (_listener, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof (int));

		if (res == -1)
		{
			throw std::runtime_error("[SERVER_LISTENING] - ERROR Setsockopt failed") ;
		}
		
		// bind the socket to an host::port 
		res = bind (_listener, rptr->ai_addr, rptr->ai_addrlen);

		if ("DEBUG" == _IRCconfig->getConfigValue("DEBUG")) // -------------------------------------
		{
			std::cout << BLU;
			std::cout << "[SERVER_LISTENING] - DEBUG Bind result <" << res << ">" << std::endl;
			std::cout << NOC;
		} // ---------------------------------------------------------------------------------------		

		if (!res)  // Success
		{
			break;
		}
		close_fd(_listener, true);
	}
	if (!rptr)
		throw std::runtime_error("[SERVER_LISTENING] - ERROR Binding failed");

	// Put the socker in a listening mod. Ready to reveive. 
	//	BACKLOG = socket's queue size after what ECONNREFUSED ist return
	if (listen (_listener, BACKLOG) == -1)
		throw std::runtime_error("[SERVER_LISTENING] - ERROR Listen failed");

}