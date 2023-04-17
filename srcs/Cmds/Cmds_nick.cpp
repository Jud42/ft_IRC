#include "Server.hpp"

void Server::Cmds_nick(int const fd_client, std::string const command)
{
	std::string newNick = command.substr(5);
	std::string	oldNickname;
	oldNickname = this->_clientList[_fd_nick_list[fd_client]]->getNickname();

    if ("DEBUG" ==_IRCconfig->getConfigValue("DEBUG")) // -------------------------------------
	{
		// retrieve error code of getaddrinfo command
		std::cout << BLU;
		std::cout << "[Server::Cmds_nick]" << std::endl;
        std::cout << " fd_client :" << fd_client << std::endl;
        std::cout << " old nick :" << oldNickname << std::endl;
		std::cout << " new nick :" << newNick << std::endl;
		std::cout << NOC;
	} // --------------------------------------------------------------------------------------

	std::map<std::string, Client>::iterator it;
	if (_clientList.count(newNick))
	{
		send(fd_client, "ERR_NICKNAMEINUSE", 18, 0);
		std::cout << "Nickname already used" << std::endl;
		return;
	}
	// update of client and maps _clientList, _fd_nick_list
	this->_clientList[oldNickname]->setNickname(newNick);
	Client	*tempClient = _clientList[oldNickname];
	_clientList.erase(oldNickname); //delete the actualclient
	_clientList.insert(std::pair<std::string, Client *>(newNick, tempClient));
	_fd_nick_list[fd_client] = newNick;
	send(fd_client, "nickname change", 18, 0);
	std::cout << " change of Nick fd: " << fd_client << "new nick : " << _fd_nick_list[fd_client] << std::endl;
}
