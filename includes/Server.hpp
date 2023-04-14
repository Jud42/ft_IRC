#ifndef SERVER_HPP
# define SERVER_HPP

#define		RED	"\033[31;1m"
#define		GRE	"\033[32;1m"
#define		YEL	"\033[33;1m"
#define		BLU	"\033[34;1m"
#define		NOC "\033[0m"

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
#include "Channel.hpp"

class ConfigFile;
class Client;
class Channel;

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
		void Cmds_CAP(int const fd_client, std::string const nickname);

	// cmd Ping - answer Pong
		void Cmds_ping(int const fd_client);
	// cmd Join - answer Pong
		void Cmds_join(int const fd_client, std::string const  channel, std::string const nickname);
	// cmd Part - answer Pong
		void Cmds_part(int const fd_client, std::string const  channel, std::string const nickname);
	// cmd Join - answer Pong
		int								_port;
		std::string						_pass;
		ConfigFile					*	_IRCconfig;
		std::string						_oper_pass;
		struct addrinfo				*	_addrs;
		int 							_listener;
		int								_nb_clients;
		char 							_hostname[HOSTNAME_SIZE];
		int								_efd;
		char							_buffer[BUFFER_SIZE];
		struct pollfd					_fds[MAX_CLIENTS + 1];
		std::map<std::string, Client>	_clientList;
		std::map<int, std::string>		_fd_nick_list;
		char 							_ipstr[INET6_ADDRSTRLEN];

		//data clients temp
		std::vector< int >				_client_fd;
		struct sockaddr					_addrclients[MAX_CLIENTS];

		//data channel
		std::map<std::string, Channel>	_channels;
};
#endif
