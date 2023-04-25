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

	//tmp
		void createConnexion();
		bool isNewClient(int &client_fd); //old treat_new
		int readFdClient(int &fd);
		void printAddressIp(int &fd);
		void logoutClient(std::vector<struct pollfd>::iterator &, int);
		void logoutServer();


	// Server_parse.cpp
		std::string parse(const std::string message, const int newListener);

	// cmd CAP - answer welcome
		void Cmds_CAP(int const fd_client, std::string const nickname);
	// Cmd inform_channel (except the user at the origin of the action triggering the message)
		void Cmds_inform_Channel(std::string const message, std::string const channel, std::string const exceptUser);
	// cmd Ping - answer Pong
		void Cmds_ping(int const fd_client);
	// cmd Join
		void Cmds_join(int const fd_client, std::string const  channel, std::string const nickname);
	// cmd Part
		std::string PrepPchannel(std::string const command);
		void Cmds_part(int const fd_client, std::string const  channel, std::string const nickname);

	// cmd nick
		void Cmds_nick(int const fd_client, std::string const command);

	// cmd user
		void Cmds_user(int const fd_client, std::string const command);
	// cmd whois
		void Cmds_whois(int const fd_client, std::string const command);
	// cmd msg / privmsg
		void Cmds_msg(int const fd_client, std::string const command);

		int								_port;
		std::string						_pass;
		ConfigFile					*	_IRCconfig;
		std::string						_oper_pass;
		struct addrinfo				*	_addrs;
		int 							_listener;
		char 							_hostname[HOSTNAME_SIZE];
		int								_efd;
		char							_buffer[BUFFER_SIZE];
		std::vector< struct pollfd >	_fds;
		std::map<std::string, Client *>	_clientList; //key nickname
		std::map<int, std::string>		_fd_nick_list; //key client_fd
		char 							_ipstr[INET6_ADDRSTRLEN];

		//data channel
		std::map<std::string, Channel * >	_channels; //key channel name without #
		std::map< int, struct sockaddr >	_addrclient;
};

void		print_all_caractere(std::string src);
std::string	find_cmd_arg(std::string buffer, std::string command);

#endif
