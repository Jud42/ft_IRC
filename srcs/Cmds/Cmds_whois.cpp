#include "Server.hpp"


// PRIVMSG dest_nickname :message

void Server::Cmds_whois(int const fd_client, std::string const command)
{
	std::string hostname = this->_hostname;

	std::string nick = find_cmd_arg(command, "WHOIS");
	if (nick.size() == 0)
		nick = this->_fd_nick_list[fd_client];
	if (_clientList.count(nick) == 0)
	{
		std::string cap_response = "401 \r\n";
        std::cout << "user does not exist: *" << nick << "*" << std::endl;
		send(fd_client, cap_response.c_str(), cap_response.length(), 0);
    }
	else
	{
		std::cout << YEL << "client: " <<  std::endl;
		std::cout << "fd: " << this->_clientList[nick]->getClientFd() << std::endl;
		std::cout << "nick: " << this->_clientList[nick]->getNickname() << std::endl;
		std::cout << "password: " << this->_clientList[nick]->getPassword() << std::endl;
		std::cout << "modes: " << this->_clientList[nick]->getModes() << std::endl;
		std::cout << "user: " << this->_clientList[nick]->get_user() << std::endl;
		std::cout << "ip: " << this->_clientList[nick]->get_ip()  << std::endl;
		std::cout << "realname: " << this->_clientList[nick]->get_realname() << NOC << std::endl;
		std::cout << "----------------------------- " <<  std::endl;

		//001     RPL_WELCOME
		std::string cap_response = "001\n";
		cap_response += "nick: " + this->_clientList[nick]->getNickname();
		cap_response += "\nuser: " + this->_clientList[nick]->get_user();
		cap_response += "\nrealname: " + this->_clientList[nick]->get_realname();
		cap_response += "\nip: " + this->_clientList[nick]->get_ip() + "\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
		send(fd_client, cap_response.c_str(), cap_response.length(), 0);


		// reponse à "WHOIS vhaefeli" demande par vanilou :kinetic.oftc.net 318 vanilou vhaefeli :End of /WHOIS list.
		cap_response = ":" + hostname + " 318 " + this->_clientList[_fd_nick_list[fd_client]]->getNickname() + " ";
		cap_response +=  nick + " :End of /WHOIS list.\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;

		send(fd_client, cap_response.c_str(), cap_response.length(), 0);
	}
}


/*
Numéro d'erreur : 401
Code d'erreur : ERR_NOSUCHNICK
Signification : Le nickname spécifié n'a pas été trouvé sur le réseau IRC.

Numéro d'erreur : 402
Code d'erreur : ERR_NOSUCHSERVER
Signification : Le serveur IRC spécifié n'a pas été trouvé sur le réseau IRC. Cela peut se produire si le serveur demandé dans la commande WHOIS n'est pas valide ou n'est pas connecté au réseau.
Numéro d'erreur : 403
Code d'erreur : ERR_NOSUCHCHANNEL
Signification : Le canal spécifié dans la commande WHOIS n'a pas été trouvé sur le serveur ou sur le réseau IRC. Cela peut se produire si le canal demandé n'existe pas ou a été supprimé.
Numéro d'erreur : 406
Code d'erreur : ERR_WASNOSUCHNICK
Signification : Le nickname spécifié dans la commande WHOIS n'a pas été trouvé sur le serveur ou sur le réseau IRC précédemment. Cela peut se produire si le nickname a été renommé, déconnecté ou n'a jamais existé sur le réseau.

*/
