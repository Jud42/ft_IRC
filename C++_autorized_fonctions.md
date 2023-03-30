Tout ce qui respecte la norme C++ 98.

# accept

```#include <sys/socket.h>```

The accept() function shall extract the first connection on the queue of pending connections, create a new socket with the same socket type protocol and address family as the specified socket, and allocate a new file descriptor for that socket. 

Sources :
  - https://linux.die.net/man/3/accept
  - https://www.geeksforgeeks.org/accept-system-call/

# bind

```#include <functional>```

Returns a function object based on fn, but with its arguments bound to args.

Calling the returned object returns the same type as fn, unless a specific return type is specified as Ret (2) (note that Ret is the only template parameter that cannot be implicitly deduced by the arguments passed to this function).

Sources :
  - https://cplusplus.com/reference/functional/bind/
  - https://www.geeksforgeeks.org/bind-function-placeholders-c/


# connect

```#include <sys/socket.h>```
  
More dedicated to the client side

The connect() function shall attempt to make a connection on a socket. The function takes the following arguments:

socket
  
  - Specifies the file descriptor associated with the socket. 
  
address
  
  - Points to a sockaddr structure containing the peer address. The length and format of the address depend on the address family of the socket. 
  
address_len
  
  - Specifies the length of the sockaddr structure pointed to by the address argument.
  
Sources : 
  - https://linux.die.net/man/3/connect

# fcntl

``` #include <unistd.h> ```

``` #include <fcntl.h> ```

The operating characteristics of sockets can be controlled with the fcntl() call. The operations to be controlled are determined by cmd. The arg parameter is a variable with a meaning that depends on the value of the cmd parameter.

Parameter
  - Description
socket
  - The socket descriptor.
cmd
  - The command to perform.
arg
  - The data associated with cmd. 

Look at the sources as description of commands must be review.

Sources :
  - https://www.ibm.com/docs/en/zvse/6.2?topic=SSB27H_6.2.0/fa2ti_call_fcntl.htm
  - https://linux.die.net/man/3/fcntl

# fstat

```#include <sys/types.h>```
```#include <sys/stat.h>```
```#include <unistd.h>```

These functions return information about a file. No permissions are required on the file itself, but-in the case of stat() and lstat() - execute (search) permission is required on all of the directories in path that lead to the file.

  -stat() stats the file pointed to by path and fills in buf.
  -lstat() is identical to stat(), except that if path is a symbolic link, then the link itself is stat-ed, not the file that it refers to.
  -fstat() is identical to stat(), except that the file to be stat-ed is specified by the file descriptor fd. 

Look at the sources to have information about the stat structure

Sources :
  - https://linux.die.net/man/2/fstat

# freeaddrinfo

```#include <sys/types.h>```
```#include <sys/socket.h>```
```#include <netdb.h>```

Look at source to have more information about the addrinfo structure.
There getaddrinfo is closely linked.

```void freeaddrinfo(struct addrinfo *res);```

Sources :
  - https://linux.die.net/man/3/freeaddrinfo

# getaddrinfo

```#include <sys/types.h>```
```#include <sys/socket.h>```
```#include <netdb.h>```

Given node and service, which identify an Internet host and a service, 
  - getaddrinfo() returns one or more addrinfo structures, each of which contains an Internet address that can be specified in a call to bind(2) or connect(2). The getaddrinfo() function combines the functionality provided by the gethostbyname(3) and getservbyname(3) functions into a single interface, but unlike the latter functions, getaddrinfo() is reentrant and allows programs to eliminate IPv4-versus-IPv6 dependencies. 

```
int getaddrinfo(const char *node, const char *service,
                const struct addrinfo *hints,
                struct addrinfo **res);
```

Sources :
  - https://linux.die.net/man/3/freeaddrinfo

# gethostbyname

```#include <netdb.h>```

The gethostbyname*() and gethostbyaddr*() functions are obsolete. Applications should use getaddrinfo(3) and getnameinfo(3) instead. 

Sources :
  - https://linux.die.net/man/3/gethostbyname


# getprotobyname

```#include <netdb.h>```

The getprotoent() function reads the next entry from the protocols database (see protocols(5)) and returns a protoent structure containing the broken-out fields from the entry. A connection is opened to the database if necessary. 

Sources :
  - https://linux.die.net/man/3/getprotobyname

# getsockname

```#include <sys/socket.h>```

get socket name

```int getsockname(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen);```

On success, zero is returned.  On error, -1 is returned, and errno is set to indicate the error.

Sources :
  - https://man7.org/linux/man-pages/man2/getsockname.2.html
                  
# htonl

```#include <arpa/inet.h>```

The htonl() function converts the unsigned integer hostlong from host byte order to network byte order. 

Sources :
  - https://linux.die.net/man/3/htonl

# htons

```#include <arpa/inet.h>```

The htons() function converts the unsigned short integer hostshort from host byte order to network byte order. 

Sources :
  - https://linux.die.net/man/3/htonl

# inet_addr

```#include <sys/socket.h>```
```#include <netinet/in.h>```
```#include <arpa/inet.h>```

The inet_addr() function converts the Internet host address cp from IPv4 numbers-and-dots notation into binary data in network byte order. If the input is invalid, INADDR_NONE (usually -1) is returned. Use of this function is problematic because -1 is a valid address (255.255.255.255). Avoid its use in favor of inet_aton(), inet_pton(3), or getaddrinfo(3) which provide a cleaner way to indicate error return. 

Sources :
  - https://linux.die.net/man/3/inet_addr

# inet_ntoa

```#include <sys/socket.h>```
```#include <netinet/in.h>```
```#include <arpa/inet.h>```

The inet_ntoa() function converts the Internet host address in, given in network byte order, to a string in IPv4 dotted-decimal notation. The string is returned in a statically allocated buffer, which subsequent calls will overwrite. 

Sources :
  - https://linux.die.net/man/3/inet_addr

# listen

```#include <sys/types.h>          /* See NOTES */```
```#include <sys/socket.h>```

listen() marks the socket referred to by sockfd as a passive socket, that is, as a socket that will be used to accept incoming connection requests using accept.

Sources :
  - https://linux.die.net/man/2/listen

# lseek

```#include <sys/types.h>```
```#include <unistd.h>```

The lseek() function repositions the offset of the open file associated with the file descriptor fd to the argument offset

The Lseek System call has been used to read some specific characters or data from a file or to write some content at the specific location of any file. This means you can read or write from in between the content of a file.

Sources : 
  - [https://linux.die.net/man/3/lseek64](https://linux.die.net/man/2/lseek)
  - https://linuxhint.com/use-lseek-system-call-c/

# ntohl

```#include <arpa/inet.h>```

The ntohl() function converts the unsigned integer netlong from network byte order to host byte order.

Sources :
  - https://linux.die.net/man/3/htonl

# ntohs

```#include <arpa/inet.h>```

The ntohs() function converts the unsigned short integer netshort from network byte order to host byte order. 

Sources :
  - https://linux.die.net/man/3/htonl

# poll (ou équivalent)

```#include <poll.h>```

poll() performs a similar task to select(2): it waits for one of a set of file descriptors to become ready to perform I/O

Sources :
  - https://linux.die.net/man/2/poll
  - https://suchprogramming.com/epoll-in-3-easy-steps/ for epoll (more performant than poll)

# setsockopt

```#include <sys/types.h>          /* See NOTES */```
```#include <sys/socket.h>```

getsockopt() and setsockopt() manipulate options for the socket referred to by the file descriptor sockfd. Options may exist at multiple protocol levels; they are always present at the uppermost socket level. 

Sources :
  - https://linux.die.net/man/2/setsockopt

# send

```#include <sys/types.h>```
```#include <sys/socket.h>```

The system calls send(), sendto(), and sendmsg() are used to transmit a message to another socket. 

The send() call may be used only when the socket is in a connected state (so that the intended recipient is known). The only difference between send() and write(2) is the presence of flags. With a zero flags argument, send() is equivalent to write(2). Also, the following call 

Sources :
  - https://linux.die.net/man/2/send

# signal

```#include <csignal>```

Specifies a way to handle the signals with the signal number specified by sig.

Sources :
  - https://cplusplus.com/reference/csignal/signal/
  - https://en.cppreference.com/w/cpp/utility/program/signal
  - https://www.enseignement.polytechnique.fr/informatique/INF478/docs/Cpp/en/cpp/utility/program/signal.html

# socket

```#include <sys/socket.h>```

Create an endpoint for communication

![image](https://user-images.githubusercontent.com/83389924/228445722-a093b09a-b70a-4b08-be6e-116692a3ad75.png)

Sources : 

  - https://pubs.opengroup.org/onlinepubs/009604499/functions/socket.html
  - https://www.geeksforgeeks.org/socket-programming-cc/
  - https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/?ref=lbp
  - https://www.bogotobogo.com/cplusplus/sockets_server_client.php
  - https://www.tutorialspoint.com/unix_sockets/socket_core_functions.htm

  - https://bousk.developpez.com/cours/reseau-c++/TCP/01-premiers-pas/
  - https://bousk.developpez.com/cours/reseau-c++/TCP/02-envoi-reception/
  - https://bousk.developpez.com/cours/reseau-c++/TCP/03-mise-en-place-protocole/
  - https://bousk.developpez.com/cours/reseau-c++/TCP/04-serveur-premiers-pas/
  - https://bousk.developpez.com/cours/reseau-c++/TCP/05-envoi-reception-serveur/
  
  Voir egalement les documents dans README.md sous Socket


# recv

```#include <sys/types.h>```
```#include <sys/socket.h>```

The recv() call is normally used only on a connected socket (see connect(2)) and is identical to recvfrom() with a NULL src_addr argument.

The recvfrom() and recvmsg() calls are used to receive messages from a socket, and may be used to receive data on a socket whether or not it is connection-oriented. 

Sources :
  - https://linux.die.net/man/2/recv



