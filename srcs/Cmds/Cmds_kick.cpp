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

	//info the commander
	std::string nick_op = _fd_nick_list[fd_client];
	std::string ip_op = this->_clientList[nick_op]->get_ip();
	std::string user_name_op = this->_clientList[nick_op]->get_user();
	//hostname server
	std::string hostname = _hostname;

	std::string resp;

	//take #channel_name
	std::string channel_name = seg[1].substr();
	channel_name.erase(0, 1); //remove # 	
	//take instance channel
	Channel *ch = _channels[channel_name];
	//verify if the commander is operator
	std::string mode_op = ch->getChannelConnectedFDMode(fd_client);
	if (mode_op == "O@") {

		std::cout << "is an operator" << std::endl;
		//take list fd clients connected on channel
		std::map<int, std::string> fds_channel;
   		fds_channel	= ch->getChannelFDsModeMap();

		//verify if the target exist in channel
		//search instance Client from nickname
		std::string target = seg[2];
		if (_clientList.find(target) != _clientList.end()) {
			int fd_target = (_clientList[target])->getClientFd();
			if (fds_channel.find(fd_target) == fds_channel.end()) {
				//client pas dans le channel ou ete deja banni
				resp = ":" + hostname + " " + "401" + nick_op +
				" " + target + " " + ":No such nick/channel\r\n";
				send(fd_client, resp.c_str(), resp.size(), 0);
				return ;
			}
			else {
			
				resp = ":" + nick_op + "!" + 
				user_name_op + "@" + ip_op + " " + 
				seg[0] + " " + seg[1] + " " + seg[2] + " " + seg[3];
			
				//std::cout << "***ohatra*** " << resp << std::endl;
				std::map<int, std::string>::iterator it;
				for(it = fds_channel.begin(); 
						it != fds_channel.end(); it++) {
			
					std::cout << "fd list: " 
						<< it->first << std::endl;
					send(it->first, resp.c_str(), resp.size(), 0);
				}
				ch->setChannelUserMode(fd_target, "b");
				std::cout << "[" << target << "]\t=> BANI =>\t" <<
					ch->getChannelConnectedFDMode(fd_target) 
						<< std::endl;
			}
		}
		else
			std::cout << "nick client n'existe pas dans [_clientList]" << std::endl;
	}
	else { //if commander is not operator

		std::cout << "is not operator" << std::endl;
		resp = ":" + hostname +  " " + "482" + " " + nick_op +
			" " + seg[1] + " " + ":You're not channel operator\r\n";
		send(fd_client, resp.c_str(), resp.size(), 0);
	}
}	
