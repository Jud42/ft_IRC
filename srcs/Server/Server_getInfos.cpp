#include "Server.hpp"

void Server::getInfos(void)
{
    struct addrinfo s_addrinfo;
	// initialise the addrinfo structure before selection of wished options
	memset (&s_addrinfo, 0, sizeof(struct addrinfo));

	// select wished options for server - pass hereafter values
	s_addrinfo.ai_family = AF_INET;    		/* allow IPv4 */
	s_addrinfo.ai_socktype = SOCK_STREAM; 	/* Stream socket */
	s_addrinfo.ai_flags = AI_PASSIVE;    	/* for wildcard IP address */

	// allocate and initialize the addrinfo structure _addrs for the given port number
	//   to free-up use freeadrinfo() see--> Server::stop

	int res = getaddrinfo (NULL, (to_str(_port)).c_str(), &s_addrinfo, &_addrs);
			
	if ("DEBUG" ==_IRCconfig->getConfigValue("DEBUG")) // -------------------------------------
	{
		// retrieve error code of getaddrinfo command 
		std::cout << BLU;
		std::cout  << "[SERVER_GETINFOS] - DEBUG Provide getaddrinfo error code" << std::endl;
		if (res)
			std::cout << " getaddrinfo KO - " << gai_strerror(res) << std::endl;
		else
			std::cout << " getaddrinfo OK" << std::endl;
		std::cout << NOC;
	} // --------------------------------------------------------------------------------------

	if (res)
		throw std::runtime_error("[SERVER-GETINFOS] - ERROR getaddrinfo failed");

	// initialise the gethostname structure before extracting _hostname ,size originnaly set to 256
	memset(_hostname, 0, sizeof(HOSTNAME_SIZE));
	res = gethostname(_hostname, HOSTNAME_SIZE);

	if ("DEBUG" ==_IRCconfig->getConfigValue("DEBUG")) // -------------------------------------
	{
		std::cout << BLU;		
		// retrieve error code of getaddrinfo command 
		std::cout << "[SERVER_GETINFOS] DEBUG - Provide gethostname value" << std::endl;
		if (res)
			std::cout << " gethostname KO - " << gai_strerror(res) << std::endl;
		else
			std::cout << " gethostname OK <" << _hostname << ">" << std::endl;
		std::cout << NOC;
	} // ---------------------------------------------------------------------------------------
	if(res)
		throw std::runtime_error("[SERVER-GETINFOS] - ERROR gethostname failed");


	// objective is to retrieve the server ip address 
	// but the result is giving 0.0.0.0 ???
	//for (struct addrinfo* p = _addrs; p != nullptr; p = p->ai_next)
	//{
	// 	void* addr;
	// 	struct sockaddr_in* ipv4 = reinterpret_cast<struct sockaddr_in*>(p->ai_addr);
	// 	addr = &(ipv4->sin_addr);

	// 	inet_ntop(s_addrinfo.ai_family, addr, _ipstr, sizeof _ipstr);
	// 	std::cout << "IP address: " << _ipstr << '\n';
	// }
}
