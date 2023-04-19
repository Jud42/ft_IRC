#include "Server.hpp"

void Server::Cmds_user(int const fd_client, std::string const command)
{
	std::string data = command.substr(5);
	size_t position = data.find("\r\n"); // find first occurency of "\r\n"
	if (position != std::string::npos) // if found
		data = data.substr(0, position - 1); // extract the string until there
	std::string username = data.substr(data.find(" ") + 1);
	username = username.substr(0, username.find(" "));
	std::string realname = data.substr(data.find(":") + 1);
	_clientList[_fd_nick_list[fd_client]]->set_data(data);
	_clientList[_fd_nick_list[fd_client]]->set_user(username);
	_clientList[_fd_nick_list[fd_client]]->set_realname(realname);

}
