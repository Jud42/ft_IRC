#include "Server.hpp"


void Server::Cmds_msg(int const fd_client, std::string const command)
{
	std::string args = find_cmd_arg(command, "PRIVMSG");
	size_t separation = args.find(":")
	if (pos_start == std::string::npos) // if not found - npos represents an invalid or not-found position
	{
		// this must never exist because the client don't send if there is no enough parameter
		return ;
	}
	std::string dest = args.substr(0, separation - 2);
	std::string msg = args.substr(separation + 1);

	std::cout << "destination : " << dest << " msg : " << msg <<std::endl;

	if ( dest[0] = '#')
	{
		dest = args.substr(1);
		if (this->_channels.count(dest) == 0)
		{
			std::string cap_response = "403 the channel doesn't exist\r\n";
			std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
			send(fd_client, cap_response.c_str(), cap_response.length(), 0);
			return ;
		}
		for(std::map <std::string, char>::iterator it = this->_channels[dest]._channelClients.begin() )
		std::map <std::string, char>    _channelClients;
	}



}
std::string cap_response = "001 You succefully change our nickname. Your new nickname is: " + newNick + "\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
		send(fd_client, cap_response.c_str(), cap_response.length(), 0);
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
