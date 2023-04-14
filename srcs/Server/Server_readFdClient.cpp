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

int Server::readFdClient(int &fd) {

	memset(&_buffer,0,256);
	int read = recv(fd, _buffer, sizeof(_buffer), 0);
	std::cout << "read : " << read << std::endl;

	if (read > 0) {

		_buffer[read] = '\0';
		std::cout << "fd: " << fd << " => [readFdClient]: "
			<< this->_buffer << std::endl;
		std::string command = this->parse(this->_buffer, fd);
		/*---cmd envoyer par defaut par le sys client---*/
		if (command.find("CAP ",0) == 0)
		{
			if (isNewClient(fd))
				this->Cmds_CAP(fd, _fd_nick_list[fd]);
			else
				return ERR_CLIENT_EXIST; //we remove this connexion
		}
		else if (command.find("PING", 0) == 0)
		{
			std::cout << "je rentre dans ping" << std::endl;
			this->Cmds_ping(fd);
		}
		/*---cmd envoyer par l'utilisateur client---*/
		else if (command.find("NICK", 0) == 0) {}
		else if (command.find("QUIT", 0) == 0)
		{
			// deconnecter le client
			std::cout << "QUIT deconnection du fd : " 
				<< fd << std::endl;
			return LOGOUT;
		}
		else if (command.find("squit", 0) == 0) { 
			std::cout << "[SERVER WILL DISCONNECT...]\n"
				<< "List [socket] before logout_server: "
				<< _fds.size() << std::endl;
			return LOGOUT_SERVER;
		}

		std::cout << "------------------------------------- " <<  std::endl;
		return SUCCESS_LOG;
	}
	return (parseError(read, fd));
}
