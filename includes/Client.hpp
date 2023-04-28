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

		std::string					_data;
		std::string					_nickname;
		std::string					_username;
		std::string					_realname;
		std::string					_password;
		std::string					_modes;
		std::vector<std::string>	_channel;
		std::vector<int>			_privMsgContactsFd;
		int							_clientFd;
		std::string					_ip;
		int							_clientInfo; // info = nick pass and user => 0 to 3
		//struct sockaddr			_addrClient;

	public:

		void 						setNickname(std::string newNick);
		std::string					getNickname();

		void						setPassword(std::string pass);
		std::string					getPassword();

		void						setModes(std::string mode);
		std::string					getModes();

		bool						findChannel(std::string channel_name);
		std::vector<std::string>	getChannel();
		void						addChannel(std::string channel);
		void						removeChannel(std::string channel);

		bool						findContactFd(int contact_fd);
		void						addContactFd(int contact_fd);
		void						delContactFd(int contact_fd);

		void						set_ip(std::string ip);
		std::string					get_ip();

		void						set_user(std::string user);
		std::string					get_user();

		void						set_realname(std::string realname);
		std::string					get_realname();

		int							getClientFd();

		void						set_data(std::string data);
		std::string					get_data();

		void						set_clientInfo(int i);
		int							get_clientInfo();

		Client();
		Client(int client_fd, std::string client_data);
		Client(Client cpyClient, std::string newNickname);
		~Client();
};

#endif
