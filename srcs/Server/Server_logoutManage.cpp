#include "Server.hpp"

void Server::logoutClient(std::vector<struct pollfd>::iterator &it, int flag) {

	if (flag == LOGOUT || flag == LOGOUT_SERVER) {

		_clientList.erase(_fd_nick_list.at(it->fd));
		_fd_nick_list.erase(it->fd);
	}
	//close & delete fd & addr
	//if ERR_CLIENT_EXIST
	_addrclient.erase(it->fd);
	close(it->fd);
	_fds.erase(it);
}

void Server::logoutServer( void ) {

 	if (_fds.size() == 0)
		return ;
	std::vector< struct pollfd >::iterator it_lst;
	it_lst = _fds.end() - 1;
	if (it_lst != _fds.begin()) {
		logoutClient(it_lst, LOGOUT);
		logoutServer();
	}
	close(it_lst->fd);
	_fds.erase(it_lst);
	std::cout << "List [socket] after logout_server: " 
		<< _fds.size() << std::endl;
}
