#include "Server.hpp"

static int parseError(int &read, int &client_fd) {

	if (read == -1) {

		// Si errno indique qu'il n'y avait pas de données à recevoir
    	if (errno == EAGAIN || errno == EWOULDBLOCK) {
        // On ne fait rien,
		// on attend simplement la prochaine itération de poll()
			std::cout << "WAIT: DATA NOT AVAILABLE" << std::endl;
			return SUCCESS_LOG;
    	}
    	// Sinon, on considère qu'il y a eu une erreur plus grave
    	else {
        	std::cerr << "Error: recv() " << client_fd << ": "
				<< strerror(errno) << std::endl;
    	}
	}
	else if (read == 0)
		std::cout << "fd: " << client_fd << " LOGOUT" << std::endl;
	return LOGOUT;
}

int Server::readFdClient(int &fd)
{
	static std::string bufferTemp = "";
	int	nocommand = 0;

	memset(&_buffer, 0, BUFFER_SIZE);
	int read = recv(fd, _buffer, sizeof(_buffer), 0);
	std::cout << "read : " << read << std::endl;

	if (read > 0)
	{
		_buffer[read] = '\0';

		std::cout << "fd: " << fd << " => [readFdClient]: " << this->_buffer << std::endl;
		std::string buffer = _buffer;
		// print_all_caractere(buffer);
		std::string command = buffer;
		std::cout << "bufferTemp" << bufferTemp << std::endl;
	// check if the command is complete
		if (buffer.find("\r\n") == std::string::npos)
		{
			if(_buffer[BUFFER_SIZE - 1] != '\0')
			{
				std::string cap_response = "message/argument too long will be cropped\r\n";
				std::cout << fd << " [Server->Client]" << cap_response << std::endl;
				buffer[read - 2] = '\r';
				buffer[read - 1] = '\n';
				std::cout << fd << " [Server->Client]" << buffer << std::endl;
				send(fd, cap_response.c_str(), cap_response.length(), 0);
				bufferTemp = "cropped";
				std::cout << "1bufferTemp" << bufferTemp << std::endl;
			}
			else
			{
				size_t found = buffer.find_last_not_of('\0');
				bufferTemp += buffer.substr(0, found + 1);
				// print_all_caractere(bufferTemp);
				found = bufferTemp.find_last_not_of('\0');
				if (bufferTemp[found] == '\n')
				{
					buffer = bufferTemp.substr(0, found) + "\r\n";
					// print_all_caractere(buffer);
					bufferTemp = "";
				}
				else
					return SUCCESS_LOG;
			}
		}
		std::cout << "status " << buffer << _fdStatus[fd] << std::endl;
	/*---client data analyse et filling---*/
		if (_fdStatus[fd] == 9)
		{
			std::cout << "je cree un client" << std::endl;
				if (isNewClient(fd, buffer))
				{
					_fdStatus[fd] = 0;
				}
				else
					return ERR_CLIENT_CONNEXION; //we remove this connexion
		}
		if (_fdStatus[fd] == 0)
		{
			std::cout << "buffer status 0:" << buffer <<  std::endl;
			if (buffer.find("NICK") != std::string::npos && this->_clientList[_fd_nick_list[fd]]->getNickname() == "#")
			{
				std::cout << "je rentre dans nick config" << std::endl;
				try
				{
					command = find_cmd_arg(buffer, "NICK");
					if (this->_clientList[_fd_nick_list[fd]]->getNickname() == "#")
					{
						this->_clientList[_fd_nick_list[fd]]->set_clientInfo(1);
						std::cout << "client info " << this->_clientList[_fd_nick_list[fd]]->get_clientInfo() << std::endl;
					}
					this->Cmds_nick(fd, command);
					if (this->_clientList[_fd_nick_list[fd]]->getNickname() == "#")
						return LOGOUT;
				}
				catch(const CmdException& e)
				{
					std::cerr << e.what() << '\n';
				}
			}
			if (buffer.find("USER")!= std::string::npos && this->_clientList[_fd_nick_list[fd]]->get_user() == "to_be_filled")
			{
				std::cout << "je rentre dans user" << std::endl;
				this->Cmds_user(fd, buffer);
				this->_clientList[_fd_nick_list[fd]]->set_clientInfo(1);
				std::cout << "client info " << this->_clientList[_fd_nick_list[fd]]->get_clientInfo() << std::endl;
			}
			std::string pass = this->_clientList[_fd_nick_list[fd]]->getPassword();
			if (buffer.find("PASS") != std::string::npos && ( pass == "0" || pass == "1" || pass == "2" || pass == "3"))
			{
				std::cout << "je rentre dans pass" << std::endl;
				try
				{
					command = find_cmd_arg(buffer, "PASS");
					if (command != _pass)
					{
						std::string cap_response = "464 ERR_PASSWDMISMATCH Wrong password\r\n";
						send(fd, cap_response.c_str(), cap_response.length(), 0);
						std::cout << "Erreur d'authentification : mot de passe invalide " << command << this->_pass << std::endl;
						_fdStatus[fd] = 2;
					}
					else
					{
						this->_clientList[_fd_nick_list[fd]]->set_clientInfo(1);
						this->_clientList[_fd_nick_list[fd]]->setPassword(command);
						std::cout << "client info " << this->_clientList[_fd_nick_list[fd]]->get_clientInfo() << std::endl;
					}
				}
				catch(const CmdException& e)
				{
					_fdStatus[fd] = 2;
					std::cerr << e.what() << '\n';
				}
			}
			if (_fdStatus[fd] != 2 && this->_clientList[_fd_nick_list[fd]]->get_clientInfo() >= 3)
			{
				_fdStatus[fd] = 1;
				std::string cap_response = "Connexion established: Enjoy!\r\n";
				std::cout << fd << " [Server->Client]" << cap_response << std::endl;
				send(fd, cap_response.c_str(), cap_response.length(), 0);
				this->Cmds_CAP(fd, _fd_nick_list[fd]);
			}
			else
			{
				std::string cap_response = "Still processing information\r\n";
				std::cout << fd << " [Server->Client]" << cap_response << std::endl;
				send(fd, cap_response.c_str(), cap_response.length(), 0);
				if (this->_clientList[_fd_nick_list[fd]]->getPassword() == "0")
					this->_clientList[_fd_nick_list[fd]]->setPassword("1");
				else if (this->_clientList[_fd_nick_list[fd]]->getPassword() == "1")
					this->_clientList[_fd_nick_list[fd]]->setPassword("2");
				else if (this->_clientList[_fd_nick_list[fd]]->getPassword() == "2")
					this->_clientList[_fd_nick_list[fd]]->setPassword("3");
				else if (this->_clientList[_fd_nick_list[fd]]->getPassword() == "3")
				{
					std::string cap_response = "Can't read the password, please reconnect\r\n";
					std::cout << fd << " [Server->Client]" << cap_response << std::endl;
					send(fd, cap_response.c_str(), cap_response.length(), 0);
					_fdStatus[fd] = 2;
				}
			}
		}
		/*---client validated---*/
		else if (_fdStatus[fd] == 1)
		{
			nocommand = 0;
			// print_all_caractere(buffer);
			if (buffer.find("PING ") != std::string::npos)
			{
				std::cout << "je rentre dans ping" << std::endl;
				this->Cmds_ping(fd);
				nocommand = 1;
			}
			if (buffer.find("WHO ") != std::string::npos)
			{
				// commande not treated and automatically sent by the client  after a join
				nocommand = 1;
			}
			if (buffer.find("JOIN ") != std::string::npos)
			{
				std::cout << "je rentre dans join" << std::endl;
				this->Cmds_join(fd, buffer, _fd_nick_list[fd]);
				nocommand = 1;
			}

			if (buffer.find("PART ") != std::string::npos)
			{
				std::cout << "je rentre dans part" << std::endl;
				this->Cmds_part(fd, buffer, _fd_nick_list[fd]);
				nocommand = 1;
			}

			/*---cmd envoye par l'utilisateur client---*/
			if (buffer.find("NICK ") != std::string::npos)
			{
				std::cout << "je rentre dans nick" << std::endl;
				try
				{
					command = find_cmd_arg(buffer, "NICK");
					this->Cmds_nick(fd, command);
					nocommand = 1;
				}
				catch(const CmdException& e)
				{
					std::cerr << e.what() << '\n';
				}
			}

			if (buffer.find("USER ")!= std::string::npos)
			{
				std::cout << "je rentre dans user" << std::endl;
				this->Cmds_user(fd, buffer);
				nocommand = 1;
			}

			if (buffer.find("WHOIS ") != std::string::npos)
			{
				std::cout << "je rentre dans whois" << std::endl;
				this->Cmds_whois(fd, buffer);
				nocommand = 1;
			}

			if (buffer.find("MODE ") != std::string::npos)
			{
				std::cout << "je rentre dans mode" << std::endl;
				this->Cmds_mode(fd);
				nocommand = 1;
			}

			if (buffer.find("PRIVMSG ") != std::string::npos)
			{
				std::cout << "je rentre dans msg" << std::endl;
				this->Cmds_msg(fd, buffer);
				nocommand = 1;
			}

			if (buffer.find("NOTICE ") != std::string::npos)
			{
				std::cout << "je rentre dans msg" << std::endl;
				this->Cmds_notice(fd, buffer);
				nocommand = 1;
			}
			if (buffer.find("KICK ") != std::string::npos)
			{
				std::cout << "je rentre dans kick" << std::endl;
				this->Cmds_kick(fd);
				nocommand = 1;
			}
			if (buffer.find("TOPIC ") != std::string::npos)
			{
				std::cout << "je rentre dans topic" << std::endl;
				this->Cmds_topic(fd, buffer);
				nocommand = 1;
			}
			if (buffer.find("INVITE ") != std::string::npos)
			{
				std::cout << "je rentre dans invite" << std::endl;
				this->Cmds_invite(fd);
				nocommand = 1;
			}
			if (buffer.find("QUIT") != std::string::npos)
			{
				// deconnecter les channels
				this->Cmds_quit(fd);
				// deconnecter le client
				std::cout << "QUIT deconnection du fd : "
					<< fd << std::endl;

				std::string cap_response = "BYE Goodbye\r\n";
				std::cout << fd << " [Server->Client]" << cap_response << std::endl;
				send(fd, cap_response.c_str(), cap_response.length(), 0);
				return LOGOUT;

				// p.ex. vhaefeli a recu lorsque vanilou a quitte: :vanilou!~vanilouH@185.25.195.181 QUIT :
			}

			if (buffer.find("squit ", 0) == 0)
			{
				std::cout << "[SERVER WILL DISCONNECT...]\n"
					<< "List [socket] before logout_server: "
					<< _fds.size() << std::endl;
				return LOGOUT_SERVER;
			}
			if (nocommand == 0 && bufferTemp != "cropped")
			{
				std::string cap_response = "Unknown command:" + buffer ;
				std::cout << fd << " [Server->Client]" << cap_response << std::endl;
				send(fd, cap_response.c_str(), cap_response.length(), 0);
			}
			if (nocommand == 0 && bufferTemp == "cropped")
				bufferTemp = "";
		}
		/*---client error password---*/

		if (_fdStatus[fd] == 2)
		{
			std::string cap_response = "464 ERR_PASSWDMISMATCH\r\n";
			std::cout << fd << " [Server->Client]" << cap_response << std::endl;
			send(fd, cap_response.c_str(), cap_response.length(), 0);
			std::cout << "Erreur d'authentification : mot de passe invalide " << this->_clientList[_fd_nick_list[fd]]->getPassword() << this->_pass << std::endl;
			cap_response = "BYE\r\n";
			std::cout << fd << " [Server->Client]" << cap_response << std::endl;
			send(fd, cap_response.c_str(), cap_response.length(), 0);
			return LOGOUT;
		}
		std::cout << "------------------------------------- " <<  std::endl;
		return SUCCESS_LOG;
	}
	return (parseError(read, fd));
}
