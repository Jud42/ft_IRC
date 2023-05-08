#include "Server.hpp"


void Server::Cmds_msg(int const fd_client, std::string const command)
{
	std::string hostname = this->_hostname;
	std::string args = find_cmd_arg(command, "PRIVMSG");
	size_t separation = args.find(":");
	std::string nick = this->_fd_nick_list[fd_client];
	if (separation == std::string::npos) // if not found - npos represents an invalid or not-found position
	{
		std::string cap_response = "the correct way to write is: PRIVMSG destination_nick -or- #destination_channel :message\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
		send(fd_client, cap_response.c_str(), cap_response.length(), 0);
	}
	else
	{
		std::string dest = args.substr(0, separation - 1); // ATTENTION DEPEND DE L'HOTE DU SERVEUR
		std::string msg = args.substr(separation + 1);

		std::cout << "destination : " << dest << " msg : " << msg <<std::endl;

		if ( dest[0] == '#')
		{
			// std::cout << "mode " << this->_channels[dest]->getChannelConnectedFDMode(fd_client) << std::endl;
			dest = dest.substr(1);
			// std::cout << "dest " << dest << std::endl;
			if (this->_channels.count(dest) == 0)
			{
				// std::string cap_response = "403 the channel doesn't exist\r\n";
				std::string cap_response = "403\r\n";
				std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
				send(fd_client, cap_response.c_str(), cap_response.length(), 0);
				return ;
			}
			if (this->_channels[dest]->getChannelConnectedFDMode(fd_client) == "b" || this->_channels[dest]->getChannelConnectedFDMode(fd_client) == "")
			{
				// std::string cap_response = :kinetic.oftc.net 404 vanilou #loutre :Cannot send to channel
				std::string cap_response =  ":" + hostname + " 404 " + this->_clientList[_fd_nick_list[fd_client]]->getNickname() + " #" + dest;
				cap_response += " :Cannot send to channel\r\n";
				std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
				send(fd_client, cap_response.c_str(), cap_response.length(), 0);
				return ;
			}

			//std::map <std::string, std::string>    channelClients = this->_channels[dest]->getMapUsers();
			std::map <int, std::string>    channelClients = this->_channels[dest]->getChannelFDsModeMap();
			for(std::map <int, std::string>::iterator it = channelClients.begin() ;it != channelClients.end(); ++it)
			{
				int fd_dest = it->first;
				if (fd_dest != fd_client)
			//std::map <std::string, std::string>::iterator it = channelClients.begin();
			//for( ; it != channelClients.end(); ++it)
			//{
			//	std::cout << "dest" << dest << std::endl;
			//	int fd_dest = this->_clientList[it->first]->getClientFd();
				std::cout << "fd_dest " << fd_dest << std::endl;
				if (fd_dest != fd_client)
				{
					std::string cap_response = ":" + nick + " PRIVMSG #" + dest + " " + msg + "\r\n";
					std::cout << fd_dest << " [Server->Client]" << cap_response << std::endl;
					send(fd_dest, cap_response.c_str(), cap_response.length(), 0);
				}
			}
		}
		else
		{
			if (this->_clientList.count(dest) == 0)
			{
				std::string cap_response = "401\r\n";
				std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
				send(fd_client, cap_response.c_str(), cap_response.length(), 0);
				return ;
			}
			int fd_dest = this->_clientList[dest]->getClientFd();
			std::string cap_response = ":" + nick + " PRIVMSG " + dest + " " + msg + "\r\n";
			std::cout << fd_dest<< " [Server->Client]" << cap_response << std::endl;
			send(fd_dest, cap_response.c_str(), cap_response.length(), 0);
			this->_clientList[nick]->addContactFd(fd_dest);
		}
	}
}

/*
[PARSE] message : PRIVMSG #salonblabla :salut

\nIVMSG #salonblabla :salut\r
\0

[PARSE] message : PRIVMSG vrock :salut

\nIVMSG vrock :salut\r
\0\0\0


ENVOI AU DESTINATAIRE

Lorsqu'un client reçoit un message dans un salon spécifique sur un serveur IRCv3 (Internet Relay Chat version 3), le serveur envoie généralement un message de type "PRIVMSG" au client pour indiquer que le message a été reçu. Ce message contient généralement les informations suivantes :

Le préfixe : Il peut s'agir du nom du serveur IRCv3 ou du pseudo de l'utilisateur qui a envoyé le message.

La commande : Dans ce cas, la commande sera "PRIVMSG", qui indique que le message est un message privé (ou "privmsg") envoyé à un salon spécifique.

Les paramètres : Les paramètres du message PRIVMSG incluent généralement le nom du salon dans lequel le message a été envoyé, ainsi que le contenu du message lui-même.

Voici un exemple de message PRIVMSG envoyé par un serveur IRCv3 à un client :

less

:irc.example.com PRIVMSG #salon Hello! Comment ça va ?

Dans cet exemple, le préfixe est "irc.example.com", la commande est "PRIVMSG", les paramètres sont "#salon" (le nom du salon) et "Hello! Comment ça va ?" (le contenu du message). Le client peut alors traiter ce message et afficher le contenu du message dans le salon spécifié.



*/
