#ifndef DEFINE_HPP
# define DEFINE_HPP

//Buffer size for HOSTNAME
#define HOSTNAME_SIZE 256

//socket's queue size after what ECONNREFUSED ist return
# define MAX_CLIENTS 10 //BACKLOG

//Buffer size
# define BUFFER_SIZE 256

//poll timeout
#define TIMEOUT -1

// colors
#define		RED	"\033[31;1m"
#define		GRE	"\033[32;1m"
#define		YEL	"\033[33;1m"
#define		BLU	"\033[34;1m"
#define		NOC "\033[0m"

//connexion
#define SUCCESS_LOG 1
#define ERR_CLIENT_EXIST 2
#define LOGOUT 3
#define LOGOUT_SERVER 4
#define MAX_JOINS_PER_LINE 10

#endif
