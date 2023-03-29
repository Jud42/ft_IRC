#include <iostream>
#include "Server.hpp"
#include "ConfigFile.hpp"

int main (int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "[MAIN] Require execution paramaters like :" << argv[0] << " <PORT> <PASSWORD>" << std::endl;
    }

	// as per document RFC7194, ports are following hit the concensus
	// 6667 for incommint IRC connections non encrypted
	// 6697 for incomming IRC connections encrypted



	// launch the irc.config loading for on-demand use
	ConfigFile IRCconfig("./srcs/irc.config");

	// std::string valueConfig = IRCconfig.getConfigValue("DEBUG");
	// return flase on other input 
	// bool DEBUG = (valueConfig == "1");

	// define the server
	Server *srv = NULL;
	try 
	{ 
		srv = new Server(argv[1], argv[2], &IRCconfig);
	}
	catch (std::exception &	e)
	{
		std::cerr <<"[MAIN] - Exception catched during srv INIT: " << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}

  /*  try { srv->run(); }
	catch (std::exception &	e)
	{
		std::cerr <<"[MAIN] - Exception catched during srv RUN: " << e.what() << std::endl;
		//sv->shutdown(NO_THROW);
		delete srv;
		exit(EXIT_FAILURE);
	}
*/

	//sv->shutdown(THROW);
	delete srv;
	exit(EXIT_SUCCESS);
	
}