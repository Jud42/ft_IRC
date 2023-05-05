#include "Server.hpp"
#include "Channel.hpp"

//clear duplicata char & char mode unknow
static int	clean_strmode(std::string & mode) {

	std::string result;
	std::string model_mode = "itkol";
	
	for (size_t i = 0; i < mode.length(); i++) {
		if (model_mode.find(mode[i]) != std::string::npos && 
			result.find(mode[i]) == std::string::npos)
		
			//if (mode[i] == 'k' && seg.size() > 3)
			//	result += mode[i];
			//else if (mode[i] != 'k')
				result += mode[i];
	}
	if (result.empty()) {

		std::cout << "mode unknow: [" << mode 
			<< "] " << std::endl;
		return 0;
	}
	mode = result;
	return 1;
}

void	Server::Cmds_mode(const int fd_client) {
	
	std::vector<std::string> seg;
	std::stringstream ss(_buffer);
	std::string word;
	while (ss >> word)
		seg.push_back(word);

	//info the commander
	std::string nick_op = _fd_nick_list[fd_client];
	std::string ip_op = this->_clientList[nick_op]->get_ip();
	std::string user_name_op = this->_clientList[nick_op]->get_user();
	//hostname server
	std::string hostname = _hostname;
	// response
	std::string resp;

	//take #channel_name
	std::string channel_name = seg[1].substr();
	channel_name.erase(0, 1); //remove # 	
	if (seg[1].find('#') != std::string::npos && 
			_channels.find(channel_name) != _channels.end()) {

		//take instance channel
		Channel *ch = _channels[channel_name];
		//verify if the commander is operator
		std::string mode_op = ch->getChannelConnectedFDMode(fd_client);
		if (mode_op == "O@") {

			std::cout << "is an operator" << std::endl;
			//take list fd clients connected on channel
			std::map<int, std::string> fds_channel;
			fds_channel	= ch->getChannelFDsModeMap();

			if (seg.size() == 2) {
				resp = ":" + hostname + " 324 " + nick_op +
					" " + seg[1] + " +" + ch->getChannelMode() + "\r\n";
				send(fd_client, resp.c_str(), resp.size(), 0);
				resp = ":" + hostname + " 329 " + nick_op +
					" " + seg[1] + " 1683281863\r\n";
				send(fd_client, resp.c_str(), resp.size(), 0);
			}
			else {		
								
				std::string mode = seg[2];
				char sign = (seg[2])[0]; // + or -
				mode.erase(0, 1);
				if (!clean_strmode(mode)) //remove doublon & mode unknow
					return ;

				std::string::reverse_iterator r_it; 
				std::string mode_actu = ch->getChannelMode();
				for (r_it = mode.rbegin(); r_it != mode.rend(); r_it++) {


						if (sign == '+' && 
							mode_actu.find(*r_it) == std::string::npos)
								mode_actu.insert(mode_actu.begin(), *r_it);
						else if (sign == '-' && 
							mode_actu.find(*r_it) != std::string::npos) 
								mode_actu.erase(mode_actu.find(*r_it));
				}

				//save the new mode of channel
				ch->setChannelMode(mode_actu);
				resp = ":" + nick_op + "!" + 
				user_name_op + "@" + ip_op + " " + seg[0] + 
				" " + seg[1] + " " + sign + mode + "\r\n";
				send(fd_client, resp.c_str(), resp.size(), 0);

				//send information to all users on channel
				std::map<int, std::string>::iterator it;
				for(it = fds_channel.begin(); 
						it != fds_channel.end(); it++) {
			
					std::cout << "fd list: " 
						<< it->first << std::endl;
					if (it->first != fd_client)
						send(it->first, resp.c_str(), resp.size(), 0);
				}

			}
							
		}
		else { //if commander is not operator

			std::cout << "is not operator" << std::endl;
			resp = ":" + hostname +  " " + "482" + " " + nick_op +
				" " + seg[1] + " " + ":You're not channel operator\r\n";
			send(fd_client, resp.c_str(), resp.size(), 0);
		}
	}
	else { //channel doesn't exist
		
		//ignore default MODE send by irssi 
		if (seg[1] == nick_op)
			return ;
		std::cout << "channel doesn't exist" << std::endl;
		resp = ":" + hostname + " 403 " + nick_op +
			" " + seg[1] + " :No such channel\r\n";
		send(fd_client, resp.c_str(), resp.size(), 0);
	}
}	
