#include <iostream>
#include "Server.hpp"
#include "ConfigFile.hpp"

int main (int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "[MAIN] Require execution paramaters like :" << argv[0] << " <PORT> <PASSWORD>" << std::endl;
		return(0);
    }
	std::string password = argv[2];
	if (password.length() < 4)
	{
        std::cerr << "[MAIN] The password must at least have 4 caracters" << std::endl;
		return(0);
    }
	// as per document RFC7194, ports are following hit the concensus
	// 6667 for incommint IRC connections non encrypted
	// 6697 for incomming IRC connections encrypted

	// launch the irc.config loading for on-demand use

	ConfigFile IRCconfig("./srcs/irc.config");

	// std::string valueConfig = IRCconfig.getConfigValue("DEBUG");
	// return flase on other input
	// bool DEBUG = (valueConfig == "DEBUG");

	// define the server
	Server *srv = NULL;
	try
	{
		srv = new Server(argv[1], argv[2], &IRCconfig);
		srv->monitoring();

		srv->stop();
	}
	catch (std::exception &	e)
	{
		std::cerr <<"[MAIN] - Exception catched during srv INIT: " << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}


//	srv->treatment();

	delete srv;
	exit(EXIT_SUCCESS);

}
