#include "Client.hpp"

Client::Client(int client_fd, std::string client_data)
: _clientFD(client_fd)
{



}

Client::~Client()
{
}

/*

client_data exemple:

CAP LS
NICK vhaefeli
USER vhaefeli vhaefeli c1r4s1.42lausanne.ch :Vanessa Haefeli

*/
