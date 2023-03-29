#ifndef SERVER_HPP
# define SERVER_HPP

#define		RED	"\033[31;1m"
#define		GRE	"\033[32;1m"
#define		YEL	"\033[33;1m"
#define		BLU	"\033[34;1m"
#define		NOC "\033[0m"

#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>

#include "to_str.hpp"
#include "ConfigFile.hpp"

class ConfigFile;

class	Server 
{

	public:

		Server(const char * port, const char *pass, ConfigFile *IRCconfig);
		~Server(void);

    private:
	// Server_getInfos.cpp
	//		void getInfos (void);
	//	void test (void);

		
		int							_port;
		std::string					_pass;
		ConfigFile				*	_IRCconfig;
		std::string					_oper_pass;
		struct addrinfo			*	_addrs;
		int 						_listener;
		int							_nb_ev;
		

	
};
#endif