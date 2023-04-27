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
	memset(&_buffer,0,256);
	sleep(5);
	int read = recv(fd, _buffer, sizeof(_buffer), 0);
	std::cout << "read : " << read << std::endl;

	if (read > 0)
	{
		_buffer[read] = '\0';
		std::cout << "fd: " << fd << " => [readFdClient]: "
			<< this->_buffer << std::endl;
			std::string buffer = _buffer;
			std::string command = buffer;
		/*---client data analyse et filling---*/
		if (_fdStatus[fd] == 0)
		{
			if (buffer.find("CAP ",0) != std::string::npos)
			{
				std::cout << "je rentre dans cap" << std::endl;
				if (isNewClient(fd))
					this->Cmds_CAP(fd, _fd_nick_list[fd]);
				else
					return ERR_CLIENT_CONNEXION; //we remove this connexion
			}
			else
			{
				if (buffer.find("NICK") != std::string::npos)
				{
					std::cout << "je rentre dans nick" << std::endl;
					try
					{
						command = find_cmd_arg(buffer, "NICK");
						this->Cmds_nick(fd, command);
						this->_clientList[_fd_nick_list[fd]]->set_clientInfo(1);
					}
					catch(const CmdException& e)
					{
						std::cerr << e.what() << '\n';
					}
				}

				if (buffer.find("USER")!= std::string::npos)
				{
					std::cout << "je rentre dans user" << std::endl;
					this->Cmds_user(fd, this->_buffer);
					this->_clientList[_fd_nick_list[fd]]->set_clientInfo(1);
				}
				if (buffer.find("PASS") != std::string::npos)
				{
					std::cout << "je rentre dans pass" << std::endl;
					try
					{
						command = find_cmd_arg(buffer, "PASS");
						if (command != _pass)
							_fdStatus[fd] = 2;
						else
						{
							this->_clientList[_fd_nick_list[fd]]->set_clientInfo(1);
							this->_clientList[_fd_nick_list[fd]]->setPassword(command);
						}
					}
					catch(const CmdException& e)
					{
						_fdStatus[fd] = 2;
						std::cerr << e.what() << '\n';
					}
				}
			}
			if (_fdStatus[fd] != 2 && this->_clientList[_fd_nick_list[fd]]->get_clientInfo() == 3)
			{
				_fdStatus[fd] = 1;
				std::string cap_response = "Connexion established: Enjoy!\r\n";
				std::cout << fd << " [Server->Client]" << cap_response << std::endl;
				send(fd, cap_response.c_str(), cap_response.length(), 0);
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
			if (buffer.find("PING") != std::string::npos)
			{
				std::cout << "je rentre dans ping" << std::endl;
				this->Cmds_ping(fd);
			}
			if (buffer.find("JOIN") != std::string::npos)
			{
				std::cout << "je rentre dans join" << std::endl;
				this->Cmds_join(fd, this->_buffer, _fd_nick_list[fd]);
			}

			if (buffer.find("PART") != std::string::npos)
			{
				std::cout << "je rentre dans part" << std::endl;
				this->Cmds_part(fd, this->_buffer, _fd_nick_list[fd]);
			}

			/*---cmd envoye par l'utilisateur client---*/
			if (buffer.find("NICK") != std::string::npos)
			{
				std::cout << "je rentre dans nick" << std::endl;
				try
				{
					command = find_cmd_arg(buffer, "NICK");
					this->Cmds_nick(fd, command);
				}
				catch(const CmdException& e)
				{
					std::cerr << e.what() << '\n';
				}
			}

			if (buffer.find("USER")!= std::string::npos)
			{
				std::cout << "je rentre dans user" << std::endl;
				this->Cmds_user(fd, this->_buffer);
			}

			if (buffer.find("WHOIS") != std::string::npos)
			{
				std::cout << "je rentre dans whois" << std::endl;
				this->Cmds_whois(fd, this->_buffer);
			}

			if (buffer.find("MODE") != std::string::npos)
			{
				std::cout << "je rentre dans mode" << std::endl;
			}

			if (buffer.find("PRIVMSG") != std::string::npos)
			{
				std::cout << "je rentre dans msg" << std::endl;
				this->Cmds_msg(fd, this->_buffer);
			}

			if (buffer.find("NOTICE") != std::string::npos)
			{
				std::cout << "je rentre dans msg" << std::endl;
				this->Cmds_notice(fd, this->_buffer);
			}

			if (buffer.find("QUIT") != std::string::npos)
			{
				// deconnecter le client
				std::cout << "QUIT deconnection du fd : "
					<< fd << std::endl;
				std::string cap_response = "BYE Goodbye\r\n";
				std::cout << fd << " [Server->Client]" << cap_response << std::endl;
				send(fd, cap_response.c_str(), cap_response.length(), 0);
				return LOGOUT;

				// p.ex. vhaefeli a recu lorsque vanilou a quitte: :vanilou!~vanilouH@185.25.195.181 QUIT :
			}

			if (buffer.find("squit", 0) == 0)
			{
				std::cout << "[SERVER WILL DISCONNECT...]\n"
					<< "List [socket] before logout_server: "
					<< _fds.size() << std::endl;
				return LOGOUT_SERVER;
			}
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
