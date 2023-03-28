#include Server.hpp

Server::Server( const char * port, const char * pass ) : _port(strtol(port, NULL, 10)), _pass(pass), _oper_pass(OPER_PASSWORD), _addrs(NULL), _listener(-1), _nb_ev(0)
{
	if (_port < 1024 || _port > 65535)
		throw std::runtime_error("port not correct");
	try
	{
        //...
	}
	catch (std::exception &e)
	{
		std::cerr << "[SERVER] - Exception catched : " << e.what() << std::endl;
        // shutdowm server
		throw e;
	}
	std::cout << "Server constructed with success" << std::endl;
	std::cout << std::left << std::setw(15) <<"Hostname : " << hostname << std::endl;
	std::cout << std::left << std::setw(15) <<"port : " << _port << std::endl;
}

Server::~Server( void ) {
	std::cout << "Server destroyed with success" << std::endl;
}

void	Server::run( void )
{
	while (1)
	{
		sleep 10
	}
	
}
