#include "Server.hpp"

Server::Server(const char *port, const char *pass, ConfigFile *IRCconfig) : 
	_port(strtol(port, NULL, 10)), 
	_pass(pass),
	_IRCconfig(IRCconfig),
	_oper_pass(_IRCconfig->getConfigValue("OPER_PASSWORD")),
	_addrs(NULL),
	_listener(-1),
	_nb_ev(0)
{
	// http://www.iana.org/assignments/service-names-port-numbers/service-names-port-numbers.xhtml
	// the port number allowed must be in the range of 1024 - 49151 (User Ports) or
	// in the range of 49152 to 65535 (Dynamic and/or Private Ports)
	if (_port < 1024 || _port > 65535)
		throw std::runtime_error("[SERVER] - Port not in expected range (1024 - 65535)");

	//std::string Debug = IRCconfig->getConfigValue("DEBUG");

	// get information about socket
	try
	{
		this->getInfos();
		test();
		
	}
	catch (std::exception &e)
	{
		
	}


}

Server::~Server( void )
{
	//freeaddrinfo(_addrs);
}

