#include "Server.hpp"

void	Server::Cmds_kick(std::string &op, std::string &channel, std::string &client) {

	Channel *channel_p = _channel.find(channel);
	std::map<std string, std::string>	*channel_users;
	std::map<std string, std::string>	it;

	channel_users = &(channel_p.getMapUsers());
	it = channel_users->find(op);
	if (it == channel_users->end()) {
		std::cout << "attention l'operateur ne figure pas dans la liste"
			<< std::endl;
		return ;
	}

	std::string mode_user = it.second;
	if (mode_user.find('#') != std::string::npos 
			|| mode_user.find('o') != std::string::npos) {
		if (setChannelUserMode(client, 'b')) {
			//mettre le client en mode banni (b)
			//utilise part() pour quitter le canal
			int fd = (_clientList.at(client))->getClientFd();
			part(fd, channel, client);
			//print sur le canal le client banni avec send()
		}
		else
			std::cout << "le clients n'existe pas" << std::endl;
		return ;
	}

	//print operateur n'a pas la permission necessaire avec send()
}
