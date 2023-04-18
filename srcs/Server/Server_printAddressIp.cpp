#include "Server.hpp"

void Server::printAddressIp(int &fd) {

	if (!_addrclient.count(fd)) {
		std::cout << "==ADDRESS IP: "
			<< " DOESN'T EXIST" << "== FD: "
			<< fd << std::endl;
		return ;
	}
	struct sockaddr addr = _addrclient.at(fd);
	struct sockaddr_in *addrin = (struct sockaddr_in *)(&addr);
	char ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addrin->sin_addr), ip_str, INET_ADDRSTRLEN);
	_clientList[_fd_nick_list[fd]]->set_ip(ip_str);
    std::cout << "==ADDRESS IP: " << ip_str
		<< "== FD: " << fd << std::endl;
}
