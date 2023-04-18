#include "Server.hpp"

void Server::Cmds_nick(int const fd_client, std::string const command)
{
	std::string newNick = command.substr(5);
	size_t position = newNick.find_last_of("\r\n"); // find last occurency of "\r\n"
	if (position != std::string::npos) { // if found
    	newNick = newNick.substr(0, position - 1); // extract the string until there
}
	std::string	oldNickname;
	oldNickname = this->_clientList[_fd_nick_list[fd_client]]->getNickname();

    if ("DEBUG" ==_IRCconfig->getConfigValue("DEBUG")) // -------------------------------------
	{
		// retrieve error code of getaddrinfo command
		std::cout << BLU;
		std::cout << "[Server::Cmds_nick]" << std::endl;
        std::cout << " fd_client :" << fd_client << std::endl;
        std::cout << " old nick :" << oldNickname << std::endl;
		std::cout << " new nick :" << newNick  << std::endl;
		std::cout << NOC << std::endl;;
	} // --------------------------------------------------------------------------------------

	std::map<std::string, Client>::iterator it;
	if (_clientList.count(newNick))
	{
		std::string cap_response = "433 Nickname already exist, please choose another\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
		send(fd_client, cap_response.c_str(), cap_response.length(), 0);
		std::cout << "Nickname already used" << std::endl;
	}
	else if (newNick.length() < 1)
	{
		std::string cap_response = "431 No new nickname given\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
		send(fd_client, cap_response.c_str(), cap_response.length(), 0);
		std::cout << "No new nickname given" << std::endl;
	}
	else if (newNick.length() > 8)
	{
		std::string cap_response = "432 Nickname " + newNick + " does not respond to standard \r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
		send(fd_client, cap_response.c_str(), cap_response.length(), 0);
		std::cout << "*" << newNick << "*" << "Nickname does not respond to standard length: " << + newNick.length() << std::endl;
	}
	else
	{
		// update of client and maps _clientList, _fd_nick_list
		this->_clientList[oldNickname]->setNickname(newNick);
		Client	*tempClient = _clientList[oldNickname];
		_clientList.erase(oldNickname); //delete the actualclient
		_clientList.insert(std::pair<std::string, Client *>(newNick, tempClient));
		_fd_nick_list[fd_client] = newNick;
		//001     RPL_WELCOME
		std::string cap_response = "001 You succefully change your nickname. Your new nickname is: " + newNick + "\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
		send(fd_client, cap_response.c_str(), cap_response.length(), 0);
		std::cout << " change of Nick fd: " << fd_client << "new nick : " << _fd_nick_list[fd_client] << std::endl;
	}
}

/*

Code de réponse 001 (RPL_WELCOME) : Il s'agit d'une réponse positive indiquant que le serveur a accepté le changement de pseudonyme et que l'utilisateur est maintenant connecté sous le nouveau pseudonyme. Le message peut ressembler à ceci : "001 : Bienvenue sur le serveur IRC. Votre pseudo est maintenant [nouveau_pseudonyme]".
Code de réponse 431 (ERR_NONICKNAMEGIVEN) : Il s'agit d'une réponse d'erreur indiquant que le client n'a pas fourni de pseudonyme dans la commande "NICK". Le message peut ressembler à ceci : "431 : Erreur - aucun pseudonyme fourni. Veuillez spécifier un pseudonyme valide".
Code de réponse 432 (ERR_ERRONEUSNICKNAME) : Il s'agit d'une réponse d'erreur indiquant que le pseudonyme fourni par le client dans la commande "NICK" est invalide selon les règles de syntaxe du protocole IRC. Le message peut ressembler à ceci : "432 : Erreur - pseudonyme invalide. Veuillez spécifier un pseudonyme valide".
Code de réponse 433 (ERR_NICKNAMEINUSE) : Il s'agit d'une réponse d'erreur indiquant que le pseudonyme fourni par le client dans la commande "NICK" est déjà utilisé par un autre utilisateur sur le serveur IRC. Le message peut ressembler à ceci : "433 : Erreur - pseudonyme déjà utilisé. Veuillez choisir un autre pseudonyme".

*/
