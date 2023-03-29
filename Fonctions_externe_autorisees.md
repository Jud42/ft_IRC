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

Look at source to have more information about the addrinfo structure

```void freeaddrinfo(struct addrinfo *res);```

Sources :
  - https://linux.die.net/man/3/freeaddrinfo

# getaddrinfo

```#include <sys/types.h>```
```#include <sys/socket.h>```
```#include <netdb.h>```

Given node and service, which identify an Internet host and a service, 
  - getaddrinfo() returns one or more addrinfo structures, each of which contains an Internet address that can be specified in a call to bind(2) or connect(2). The getaddrinfo() function combines the functionality provided by the gethostbyname(3) and getservbyname(3) functions into a single interface, but unlike the latter functions, getaddrinfo() is reentrant and allows programs to eliminate IPv4-versus-IPv6 dependencies. 

```int getaddrinfo(const char *node, const char *service,
                const struct addrinfo *hints,
                struct addrinfo **res);
```

Sources :
  - https://linux.die.net/man/3/freeaddrinfo

# gethostbyname

# getprotobyname

# getsockname

# htonl

# htons

# inet_addr

# inet_ntoa

# listen

# lseek

# ntohl

# ntohs

# poll (ou équivalent)

# setsockopt

# send

# signal

# socket

Specifies a socket that was created with socket(), has been bound to an address with bind(), and has issued a successful call to listen(). 


![image](https://user-images.githubusercontent.com/83389924/228445722-a093b09a-b70a-4b08-be6e-116692a3ad75.png)

Sources: 

  - https://www.geeksforgeeks.org/socket-programming-cc/
  - https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/?ref=lbp


# recv

