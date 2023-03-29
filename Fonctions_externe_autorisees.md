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

```
#include <unistd.h>

#include <fcntl.h>
```

The operating characteristics of sockets can be controlled with the fcntl() call. The operations to be controlled are determined by cmd. The arg parameter is a variable with a meaning that depends on the value of the cmd parameter.

Parameter
  - Description
socket
  - The socket descriptor.
cmd
  - The command to perform.
arg
  - The data associated with cmd. 

Sources :
  - https://www.ibm.com/docs/en/zvse/6.2?topic=SSB27H_6.2.0/fa2ti_call_fcntl.htm

# fstat

# freeaddrinfo

# getaddrinfo

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

