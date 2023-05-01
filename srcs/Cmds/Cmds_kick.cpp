#include "Server.hpp"
#include "Channel.hpp"

bool	isCorrectInput(std::string buffer, std::vector<std::string> &seg) {

	std::stringstream ss(buffer);
	std::string word;
	while (ss >> word)
		seg.push_back(word);
	//format normal => KICK #channel_name target_name :reason
	//if [reason] is not specifie default value => :target_name
	if (seg.size() != 4 || seg[1].find('#') == std::string::npos
		|| seg[3].find(':') == std::string::npos) {
		std::cout << "Error: input for KICK from _buffer" 
		<< std::endl;
		return false;
	}
	if (seg[3].size() == 1) //":\r\n"
		seg[3].append(seg[2]); //":targer_name"
	seg[3].append("\r\n");
	//std::cout << seg[3] << "\tsize: " << seg[3].size() << std::endl;
	return true;
}

void	Server::Cmds_kick(const int fd_client) {
	
	std::vector<std::string> seg;
	if (!isCorrectInput(_buffer, seg))	
		return ;
	std::string channel_name = seg[1].erase(0, 1); //remove #
	std::string target = seg[2];
	Channel *ch = _channels[channel_name];	
	//search nickname target a partir du fd dans channlclient;
	std::cout << "list: " << (clients.begin())->first << std::endl;
	if (clients.find(target) != clients.end()) {
		//client pas dans le channel

	std::string nick_op = _fd_nick_list[fd_client];
	std::string ip_op = this->_clientList[nick_op]->get_ip();
	std::string user_name_op = this->_clientList[nick_op]->get_user();
	std::string mode_op = ch->getChannelConnectedFDMode(fd_client);
	//std::string hostname = this->_hostname;

	if (!mode_op.compare("O@") || !mode_op.compare("o")) {
		std::string resp = ":" + nick_op +
		"!" + user_name_op + "@" + ip_op + " " + 
		seg[0] + " " + seg[1] + " " + seg[2] + " " + seg[3];
		std::cout << "***ohatra*** " << resp << std::endl;
		std::map<std::string, std::string>::iterator it;
		for(clients.begin() = it; it != clients.end(); it++) {
			
			int fd = (_clientList[it->first])->getClientFd();
			if (it->second != "b")
				send(fd, resp.c_str(), resp.size(), 0);
		}
	}
	else {
		//send client not operator
	} 
	}
	return ;
}
