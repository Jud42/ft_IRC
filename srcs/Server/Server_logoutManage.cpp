#include "Server.hpp"

void Server::logoutClient(std::vector<struct pollfd>::iterator &it, int flag)
{
	int fdDel = it->fd;
	std::cout << "fd " << fdDel << "deleting:" << std::endl;
	if (flag == LOGOUT || flag == LOGOUT_SERVER)
	{
		this->Cmds_quit(it->fd);
		delete(_clientList[_fd_nick_list[it->fd]]);
		_clientList.erase(_fd_nick_list.at(it->fd));
		std::cout << "client deleted" << std::endl;
		_fd_nick_list.erase(it->fd);
		std::cout << "nickname  from fd_nick_list deleted" << std::endl;
	}
	//close & delete fd & addr
	//if ERR_CLIENT_EXIST
	_addrclient.erase(it->fd);
	std::cout << "addrclient deleted" << std::endl;
	close(it->fd);
	std::cout << "fd closed" << std::endl;
	_fds.erase(it);
	_fdStatus.erase(fdDel);
	std::cout << "it from _fds deleted" << std::endl;
	std::cout << "everything from " << fdDel << "deleted" << std::endl;
}

void Server::logoutServer( void )
{
	std::cout << RED << "logoutServer " << NOC << std::endl;
 	if (_fds.size() == 0)
		return ;
	std::vector< struct pollfd >::iterator it_lst;
	it_lst = _fds.end() - 1;
	if (it_lst != _fds.begin())
	{
		logoutClient(it_lst, LOGOUT);
		logoutServer();
	}
	if (it_lst->fd == _listener)
	{
		close(it_lst->fd);
		_fds.erase(it_lst);
	}
	std::cout << "List [socket] after logout_server: "
		<< _fds.size() << std::endl;
}
