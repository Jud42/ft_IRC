#include "Server.hpp"

void Server::logoutClient(std::vector<struct pollfd>::iterator &it, int flag) {

	if (flag == LOGOUT) {

		_clientList.erase(_fd_nick_list.at(it->fd));
		_fd_nick_list.erase(it->fd);
	}
	//close & delete fd & addr
	//if ERR_CLIENT_EXIST
	close(it->fd);
	_fds.erase(it);
	_addrclient.erase(it->fd);
}
