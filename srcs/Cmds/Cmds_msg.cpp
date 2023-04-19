#include "Server.hpp"

// PRIVMSG nicknamedest :message

void Server::Cmds_msg(int const fd_client, std::string const command)
{
	std::string newNick = command.substr(5);
	size_t position = newNick.find_last_of("\r\n"); // find last occurency of "\r\n"
	if (position != std::string::npos) { // if found
    	newNick = newNick.substr(0, position); // extract the string until there
}
	std::string	oldNickname;
	oldNickname = this->_clientList[_fd_nick_list[fd_client]]->getNickname();


	std::map<std::string, Client>::iterator it;
	if (_clientList.count(newNick))
	{
		std::string cap_response = "433 Nickname already exist, please choose another\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
		send(fd_client, cap_response.c_str(), cap_response.length(), 0);
		std::cout << "Nickname already used" << std::endl;
	}
	else if (newNick.length() < 1)
	{
		std::string cap_response = "431 No new nickname given\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
		send(fd_client, cap_response.c_str(), cap_response.length(), 0);
		std::cout << "No new nickname given" << std::endl;
	}
	else if (newNick.length() > 8)
	{
		std::string cap_response = "432 Nickname " + newNick + " does not respond to standard \r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
		send(fd_client, cap_response.c_str(), cap_response.length(), 0);
		std::cout << "*" << newNick << "*" << "Nickname does not respond to standard length: " << + newNick.length() << std::endl;
	}
	else
	{
		// update of client and maps _clientList, _fd_nick_list
		this->_clientList[oldNickname]->setNickname(newNick);
		Client	*tempClient = _clientList[oldNickname];
		_clientList.erase(oldNickname); //delete the actualclient
		_clientList.insert(std::pair<std::string, Client *>(newNick, tempClient));
		_fd_nick_list[fd_client] = newNick;
		//001     RPL_WELCOME
		std::string cap_response = "001 You succefully change zour nickname. Your new nickname is: " + newNick + "\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
		send(fd_client, cap_response.c_str(), cap_response.length(), 0);
		std::cout << " change of Nick fd: " << fd_client << "new nick : " << _fd_nick_list[fd_client] << std::endl;
	}
}

/*
[PARSE] message : PRIVMSG #salonblabla :salut

\nIVMSG #salonblabla :salut\r
\0

[PARSE] message : PRIVMSG vrock :salut

\nIVMSG vrock :salut\r
\0\0\0

*/
