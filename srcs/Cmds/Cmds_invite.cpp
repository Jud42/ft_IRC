#include "Server.hpp"
#include "Channel.hpp"

void	Server::Cmds_invite(int fd_client) {
	
	std::vector<std::string> seg;
	std::stringstream ss(_buffer);
	std::string word;
	while (ss >> word)
		seg.push_back(word);

	
	//hostname server
	std::string hostname = _hostname;
	//nickname commander
	std::string nick_op = _fd_nick_list[fd_client];
	//nickname target
	std::string target = seg[1];


	std::string resp;

	//take #channel_name
	std::string channel_name = seg[2].substr();
	channel_name.erase(0, 1); //remove # 	
	if (seg[2].at(0) == '#' && _channels.find(channel_name) != _channels.end()) {
		
		//take instance channel
		Channel *ch = _channels[channel_name];
		std::cout << "channel_name: " << ch->getChannelName() << std::endl; 

		if (_clientList.find(target) != _clientList.end()) {

			//take list fd clients connected on channel
			std::map<int, std::string> fds_channel;
			fds_channel	= ch->getChannelFDsModeMap();
			int fd_target = (_clientList[target])->getClientFd();

			//check target on channel
			if (fds_channel.find(fd_target) != fds_channel.end()) {
				
				std::cout << "target is already on channel" 
					<< std::endl;
				/*	:hostname_server 443 nick_commander nick_invited 
					#channel_name :is already on channel	*/
				resp = ":" + hostname + " 443 " + nick_op +
					" " + target + " " + seg[2] + 
						" :is already on channel\r\n";
			}
			else { //target not on channel

				std::cout << "target doesn't exist on channel" 
						<< std::endl;
				//fd_client = fd_target;	
				resp = ":" + hostname + " 341 " + nick_op +
					" " + target + " " + seg[2] + "\r\n";
				send(fd_target, resp.c_str(), resp.size(), 0);
				ch->setChannelInvite(fd_target);
			}
		}
		else { //target doesn't exist anywhere

			std::cout << "target doesn't exist on server" << std::endl;
			resp = ":" + hostname + " 401 " + nick_op +
				" " + target + " :No such nick/channel\r\n";
		}
	}
	else { //channel doesn't exist
	
		std::cout << "channel doesn't exist" << std::endl;
		resp = ":" + hostname + " 403 " + nick_op +
			" " + seg[2] + " :No such channel\r\n";
	}
	send(fd_client, resp.c_str(), resp.size(), 0);
}	
