#include "Server.hpp"

Server::Server(const char *port, const char *pass, ConfigFile *IRCconfig) :
	_port(atoi(port)),
	_pass(pass),
	_IRCconfig(IRCconfig),
	_oper_pass(_IRCconfig->getConfigValue("OPER_PASSWORD")),
	_addrs(NULL),
	_listener(-1),
	_channels(),
	_addrclient()
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
		this->listening();
		//this->monitoring();

	}
	catch (std::exception &e)
	{
		std::cerr << "[SERVER] - Exception catched : " << e.what() << std::endl;
		this->stop();
		throw e;
	}
	std::cout << "[SERVER] - Server constructed with success" << std::endl;
	std::cout << std::left << std::setw(15) <<"Hostname : " << _hostname << std::endl;
	std::cout << std::left << std::setw(15) <<"port : " << _port << std::endl;

	//set 
	memset(&_fds, 0, sizeof(_fds));
	

}

Server::~Server( void ) { 
	std::cout << "Class Server [DESTROYED] :)" << std::endl;
}

