#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "define.hpp"
# include <iostream>
# include <string>

class Client
{
private:

	std::string _nickname;
	std::string _username;
	std::string _realname;
	std::string _password;
	std::string _modes;

	int			_clientFd;

public:



	void setNickname(std::string newNick);
	std::string getNickname();

	int
	Client(/* args */);
	~Client();
};

#endif
