#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <iomanip>
#include <arpa/inet.h>

#include <poll.h>
#include <string>
#include <cstring>
#include <vector>


#include "to_str.hpp"
#include "define.hpp"
#include "ConfigFile.hpp"

class ConfigFile;

class	Server
{

	public:
	// The server might never be copied so no definition of server copy and server assignment
		Server(const char * port, const char *pass, ConfigFile *IRCconfig);
		~Server(void);
	// Server_stop.cpp
		void stop (void);
	// Server_treatment.cpp
		void treatment (int client_fd);
	// Server_monitoring.cpp
		void monitoring (void);

    private:
	// Server_getInfos.cpp
			// Server_getInfos.cpp
		void getInfos (void);
	// Server_closeFD.cpp
		void close_fd (int &fd, bool exception);
	// Server_listening.cpp
		void listening (void);


	// Server_parse.cpp
		std::string parse(const std::string message, const int newListener);

	// cmd CAP - answer welcome
		void Cmds_CAP(int const newListener, std::string const nickname);

	// cmd Ping - answer Pong
		void Cmds_ping(int const newListener);

		int							_port;
		std::string					_pass;
		ConfigFile				*	_IRCconfig;
		std::string					_oper_pass;
		struct addrinfo			*	_addrs;
		int 						_listener;
		std::vector< int >			_client_fd;

		int							_nb_client;
		char 						_hostname[HOSTNAME_SIZE];
		int							_efd;
		char						_buffer[BUFFER_SIZE];
};
#endif
