# Structure

## Configuration information
- irc.config

## Starting of the server
- ./ircserv <PORT> <PASSWORD>
- <PORT> is usually 6667.


### Object : ConfigFile

Loading and provide access to information stored into irc.config at starting.

To get the referenced value : getConfigValue()

In case nothing is found, the value returned is "".
  
### Object : Server

Object not allowed for copy / Assignation.

#### Constructor

Check of ports values performed - accepted range 1024 to 65535.

see : http://manpagesfr.free.fr/man/man3/getaddrinfo.3.html

struct addrinfo {
    int              ai_flags;
    int              ai_family;
    int              ai_socktype;
    int              ai_protocol;
    size_t           ai_addrlen;
    struct sockaddr *ai_addr;
    char            *ai_canonname;
    struct addrinfo *ai_next;
};


#### Destructor


  





