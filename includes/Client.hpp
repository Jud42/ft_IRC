#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "define.hpp"
# include <iostream>
# include <string>
# include "ConfigFile.hpp"
# include "Server.hpp"

class Channel;

class Client
{
	private:

		std::string				_nickname;
		std::string				_username;
		// std::string			_realname;
		std::string				_password;
		std::string				_modes;
		std::vector<Channel>	_channel;
		int						_clientFd;
		//struct sockaddr		_addrClient;

	public:

		void 					setNickname(std::string newNick);
		std::string				getNickname();
		std::string				getPassword();
		std::string				getModes();
		bool					findChannel();
		std::vector<Channel>	getChannel();
		void					addChannel(std::vector<Channel>	channel);

		int						getClientFd();

		Client();
		Client(int client_fd, char *client_data);
		~Client();
};

#endif
