#include "Server.hpp"

void	Server::stop(void)
{  
	
    int res;
    struct sockaddr_storage peer_addr;
    socklen_t peer_addr_len;

	
		res = recvfrom(_listener, _buffer, BUFFER_SIZE, 0,
					(struct sockaddr *) &peer_addr, &peer_addr_len); 
		//res = recv(fds[i].fd, buf sizeof(buf), 0);
		if (res < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				perror("  recv() failed");
				//close_conn = TRUE;
			}
		}


}