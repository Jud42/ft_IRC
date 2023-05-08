#include "Server.hpp"
#include "Channel.hpp"

static int	allIsDigit(std::string &str) {
	
	std::string::iterator it = str.begin();
	std::string result;
	for (; it != str.end(); it++) {
		if (!isdigit(*it))
			break ;
		result += *it;
	}
	if (result.empty()) {
		str = " ";
		return 0;
	}
	str = result;
	return 1;
}

//clear duplicata char & char mode unknow
static int	clean_strmode(std::vector<std::string> &seg, Channel &ch) {

	std::string result;
	std::string mode = seg[2];
	char sign = seg[2][0];
	std::string model_mode = "itkol";
	size_t index_arg = 3;
	
	//start i to 1 for pass the sign
	for (size_t i = 1; i < mode.length(); i++) {

		if (model_mode.find(mode[i]) != std::string::npos && 
			result.find(mode[i]) == std::string::npos) {

			if (mode[i] == 'l' && seg.size() > index_arg 
			&& allIsDigit(seg[index_arg])) {
				result += mode[i];
				if (sign == '+')  
					ch.setChannelLimit(std::atoi(seg[index_arg++].c_str()));
				else if (sign == '-')
					ch.setChannelLimit(0);
			}
			else if (mode[i] == 'k' && seg.size() > index_arg) {
				result += mode[i];
				if (sign == '+')  
					ch.setChannelPass(seg[index_arg++]);
				else if (sign == '-')
					ch.setChannelPass(" ");
			}
			else if (mode[i] != 'k' && mode[i] != 'l')
				result += mode[i];
		}
	}
	if (result.empty()) {

		std::cout << "mode unknow: [" << mode 
			<< "] " << std::endl;
		return 0;
	}
	seg[2] = seg[2][0] + result;
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
								
				if (!clean_strmode(seg, *ch)) //remove doublon & mode unknow
					return ;
				char sign = (seg[2])[0]; // + or -
				std::string mode = seg[2];
				mode.erase(0, 1); //remove sign
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
				//take all argument if they exist
				std::string end;
				if (sign == '+') {
					for (size_t i = 3; i < seg.size(); i++) {
						if (seg[i] != " ")
							end += " " + seg[i];
					}
				}
				end += "\r\n";

				//save the new mode of channel
				ch->setChannelMode(mode_actu);
				resp = ":" + nick_op + "!" + 
				user_name_op + "@" + ip_op + " " + seg[0] + 
				" " + seg[1] + " " + seg[2] + end;
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
