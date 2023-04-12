#ifndef SERVER_HPP
# define SERVER_HPP

#include <sys/socket.h>
#include <iostream>
#include <cstdlib>
#include <sys/types.h>
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
#include "Client.hpp"

class ConfigFile;
class Client;

class	Server
{

	public:
	// The server might never be copied so no definition of server copy and server assignment
		Server(const char * port, const char *pass, ConfigFile *IRCconfig);
		~Server(void);
	// Server_stop.cpp
		void stop (void);

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
	// Server_treatment.cpp
		void treatment (int client_fd);
	// Server_treatment_new.cpp creation new client
		int treatment_new(int client_fd);


	// Server_parse.cpp
		std::string parse(const std::string message, const int newListener);

	// cmd CAP - answer welcome
		void Cmds_CAP(int const newListener, std::string const nickname);

	// cmd Ping - answer Pong
		void Cmds_ping(int const newListener);
<<<<<<< HEAD

		int								_port;
		std::string						_pass;
		ConfigFile					*	_IRCconfig;
		std::string						_oper_pass;
		struct addrinfo				*	_addrs;
		int 							_listener;
		std::vector< int >				_client_fd;
		std::map<std::string, Client>	_clientList;
		std::map<int, std::string>		_fd_nick_list;
		int								_nb_client;
		char 							_hostname[HOSTNAME_SIZE];
		int								_efd;
		char							_buffer[BUFFER_SIZE];
		struct pollfd					_fds[MAX_CLIENTS + 1];
=======
	
		int							_port;
		std::string					_pass;
		ConfigFile				*	_IRCconfig;
		std::string					_oper_pass;
		struct addrinfo			*	_addrs;
		int 						_listener;
		int							_nb_clients;
		char 						_hostname[HOSTNAME_SIZE];
		int							_efd;
		char						_buffer[BUFFER_SIZE];
		struct pollfd				_fds[MAX_CLIENTS + 1];

		//data clients temp
		std::vector< int >			_client_fd;
		struct sockaddr				_addrclients[MAX_CLIENTS];
>>>>>>> 6540c079bd55af3d910656544d4d3696bf3c8463
};
#endif
