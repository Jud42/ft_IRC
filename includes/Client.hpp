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
		std::vector<int>			_privMsgContactsFd;
		int							_clientFd;
		std::string					_ip;
		int							_clientInfo; // info = nick pass and user => 0 to 3
		//struct sockaddr			_addrClient;

	public:

		void 						setNickname(std::string newNick);
		const std::string			&getNickname() const;

		void						setPassword(std::string pass);
		const std::string			&getPassword() const;

		void						setModes(std::string mode);
		const std::string			&getModes() const;

		bool						findContactFd(int contact_fd);
		void						addContactFd(int contact_fd);
		void						delContactFd(int contact_fd);
		const std::vector<int>		&getContactsFd() const;

		void						set_ip(std::string ip);
		const std::string			&get_ip() const;

		void						set_user(std::string user);
		const std::string			&get_user() const;

		void						set_realname(std::string realname);
		const std::string			&get_realname() const;

		const int					&getClientFd() const;

		void						set_data(std::string data);
		const std::string			&get_data() const;

		void						set_clientInfo(int i);
		const int					&get_clientInfo() const;

		Client();
		Client(int client_fd, std::string client_data);
		Client(Client cpyClient, std::string newNickname);
		~Client();
};

#endif
