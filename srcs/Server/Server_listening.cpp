#include "Server.hpp"

void Server::listening(void)
{
	// review the list of address structures returned by getaddrinfo.
    // stop when the the socket and bind calls are successful. 

    
    int  optval = 1; // required by setsockopt : std value
	_listener = socket (_addrs->ai_family, _addrs->ai_socktype, _addrs->ai_protocol);
	if (_listener == -1)
			throw std::runtime_error("[SERVER_LISTENING] - ERROR socket() failed") ;

	if ("DEBUG" ==_IRCconfig->getConfigValue("DEBUG")) // -------------------------------------
	{
		std::cout << BLU;
		std::cout << "[SERVER_LISTENING] - DEBUG Socket result <" << _listener << ">" << std::endl;
		std::cout << NOC;
	} // --------------------------------------------------------------------------------------

	// configure option on a socket
	// SOL_SOCKET for all sockets
	// SO_REUSEADDR indicates that the rules used in validating addresses supplied in 
	int res = setsockopt (_listener, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof (int));
	if (res == -1)
		throw std::runtime_error("[SERVER_LISTENING] - ERROR setsockopt() failed") ;
		
	// bind the socket to an local address 
	res = bind (_listener, _addrs->ai_addr, _addrs->ai_addrlen);
	if (res == -1)
		throw std::runtime_error("[SERVER_LISTENING] - ERROR binding() failed");
	
	if ("DEBUG" == _IRCconfig->getConfigValue("DEBUG")) // -------------------------------------
	{
		std::cout << BLU;
		std::cout << "[SERVER_LISTENING] - DEBUG Bind result <" << res << ">" << std::endl;
		std::cout << NOC;
	} // ---------------------------------------------------------------------------------------		

	//close_fd(_listener, true);

	// Put the socker in a listening mod. Ready to reveive. 
	//	BACKLOG = socket's queue size after what ECONNREFUSED ist return
	if (listen (_listener, MAX_CLIENTS) == -1)
		throw std::runtime_error("[SERVER_LISTENING] - ERROR Listen failed");
	if ("DEBUG" == _IRCconfig->getConfigValue("DEBUG")) // -------------------------------------
	{
		std::cout << BLU;
		std::cout << "[SERVER_LISTENING] - Socket mode listen ON" << std::endl;
		std::cout << NOC;
	} 

	// Configuration socket non bloquant
	int flags = fcntl(_listener, F_GETFL, 0);
    fcntl(_listener, F_SETFL, flags | O_NONBLOCK);
}
