#include "Server.hpp"

void Server::getInfos(void)
{
    


    struct addrinfo s_addrinfo;
	memset (&s_addrinfo, 0, sizeof(struct addrinfo));

	// select info setting
	s_addrinfo.ai_family = AF_INET;    		/* allow IPv4 */
	s_addrinfo.ai_socktype = SOCK_STREAM; 	/* Stream socket */
	s_addrinfo.ai_flags = AI_PASSIVE;    	/* for wildcard IP address */

	if (getaddrinfo (NULL, (to_str(_port)).c_str(), &s_addrinfo, &_addrs))
		throw std::runtime_error("getaddrinfo failed");

	//	if(gethostname(hostname, HOSTNAME_SIZE))
	//		throw std::runtime_error("getaddr(host) info failed");
}