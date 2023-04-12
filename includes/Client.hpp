#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "define.hpp"
# include <iostream>
# include <string>
# include "ConfigFile.hpp"
# include "Server.hpp"

class Client
{
	private:

		std::string			_nickname;
		std::string			_username;
		// std::string			_realname;
		std::string			_password;
		std::string			_modes;
		std::vector<std::string>	_canal;
		int					_clientFd;
		// struct sockaddr		_addrClient;

	public:

		void setNickname(std::string newNick);
		std::string getNickname();
		std::string getPassword();
		std::string getModes();
		std::vector<std::string>	getCanal();
		int	getClientFd();

		void setModes(std::string mode);

		Client();
		Client(int client_fd, char *client_data);
		~Client();
};

#endif
