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
		std::string cap_response = "401 user does not exist\r\n";
        std::cout << "user does not exist: *" << nick << "*" << std::endl;
		send(fd_client, cap_response.c_str(), cap_response.length(), 0);
    }
	else
	{
		// :kinetic.oftc.net 311 vanilou vhaefeli ~vhaefeli 185.25.195.181 * :Vanessa Haefeli
		std::string cap_response =  ":" + hostname + " 311 " + this->_clientList[_fd_nick_list[fd_client]]->getNickname() + " " + nick;
		cap_response += " ~" + this->_clientList[nick]->get_user() + " " + this->_clientList[nick]->get_ip() + " * :" + this->_clientList[nick]->get_realname() + "\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
		send(fd_client, cap_response.c_str(), cap_response.length(), 0);
		// :kinetic.oftc.net 312 vanilou vhaefeli coulomb.oftc.net :London, United Kingdom
		cap_response =  ":" + hostname + " 312 " + this->_clientList[_fd_nick_list[fd_client]]->getNickname() + " " + nick;
		cap_response += " " + hostname + ":Renens, Switzerland\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
		send(fd_client, cap_response.c_str(), cap_response.length(), 0);
		// :kinetic.oftc.net 338 vanilou vhaefeli 185.25.195.181 :actually using host
		cap_response =  ":" + hostname + " 338 " + this->_clientList[_fd_nick_list[fd_client]]->getNickname() + " " + nick;
		cap_response += " " + this->_clientList[nick]->get_ip() + " :actually using host\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
		send(fd_client, cap_response.c_str(), cap_response.length(), 0);
		if (this->_clientList[_fd_nick_list[fd_client]]->getNickname() == nick)
		{
			// :kinetic.oftc.net 275 vanilou vanilou :is connected via SSL (secure link)

			// :kinetic.oftc.net 317 vanilou vanilou 63 1682519612 :seconds idle, signon time
		}
		// :kinetic.oftc.net 318 vanilou vanilou :End of /WHOIS list.
		cap_response = ":" + hostname + " 318 " + this->_clientList[_fd_nick_list[fd_client]]->getNickname() + " ";
		cap_response +=  nick + " :End of /WHOIS list.\r\n";
		std::cout << fd_client << " [Server->Client]" << cap_response << std::endl;
		send(fd_client, cap_response.c_str(), cap_response.length(), 0);
		std::cout << YEL << "info client: " <<  std::endl;
		std::cout << "fd: " << (this->_clientList[_fd_nick_list[fd_client]])->getClientFd() << std::endl;
		std::cout << "nick: " << (this->_clientList[_fd_nick_list[fd_client]])->getNickname() << std::endl;
		std::cout << "password: " << (this->_clientList[_fd_nick_list[fd_client]])->getPassword() << std::endl;
		std::cout << "modes: " << (this->_clientList[_fd_nick_list[fd_client]])->getModes() << std::endl;
		std::cout << "user: " << (this->_clientList[_fd_nick_list[fd_client]])->get_user() << std::endl;
		std::cout << "ip(temp): " << (this->_clientList[_fd_nick_list[fd_client]])->get_ip()  << std::endl;
		std::cout << "realname: " << (this->_clientList[_fd_nick_list[fd_client]])->get_realname() << NOC << std::endl;
		std::cout << "----------------------------- " <<  std::endl;
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


reponse:  a vanilou:

<< WHOIS vhaefeli
>> :kinetic.oftc.net 311 vanilou vhaefeli ~vhaefeli 185.25.195.181 * :Vanessa Haefeli
--> whois event
>> :kinetic.oftc.net 312 vanilou vhaefeli coulomb.oftc.net :London, United Kingdom
--> whois default event
>> :kinetic.oftc.net 338 vanilou vhaefeli 185.25.195.181 :actually using host
--> whois default event
>> :kinetic.oftc.net 318 vanilou vhaefeli :End of /WHOIS list.
--> whois end
<< WHOIS vanilou
>> :kinetic.oftc.net 311 vanilou vanilou ~vanilouH 185.25.195.181 * :Vanilou Haefeli
--> whois event
>> :kinetic.oftc.net 312 vanilou vanilou kinetic.oftc.net :London, United Kingdom
--> whois default event
>> :kinetic.oftc.net 338 vanilou vanilou 185.25.195.181 :actually using host
--> whois default event
>> :kinetic.oftc.net 275 vanilou vanilou :is connected via SSL (secure link)
--> whois default event
>> :kinetic.oftc.net 317 vanilou vanilou 63 1682519612 :seconds idle, signon time
--> whois default event
>> :kinetic.oftc.net 318 vanilou vanilou :End of /WHOIS list.
*/
