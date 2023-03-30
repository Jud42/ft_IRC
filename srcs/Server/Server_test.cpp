#include "Server.hpp"

void Server::test(void)
{
    std::cout << "TEST"   << std::endl;

    int sockfd = socket(AF_LOCAL, SOCK_STREAM,0);

    int setsockopt(int sockfd, int level, int optname,  const void *optval, socklen_t optlen);

    int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

    int listen(int sockfd, int backlog);

}