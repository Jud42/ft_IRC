# ft_IRC

A chat server implementing the IRC (Internet Relay Chat) protocol, developed in C++98. The server allows users to connect, create and join chat channels, send messages, and interact with other users using IRC commands. This project was carried out in collaboration with two other talented members of my team. I had the opportunity to actively contribute to the implementation of essential features such as connection management, mode handling, and the implementation of specific commands. I enjoyed working on these aspects and contributing to the overall project.

> We did not need to develop the client or handle server-to-server communication.


* Program name: `ircserv`
* Server adrress: `127.0.0.1` or `hostname`
* Port: `6667`
* Library used: `socket, netdb, inet, poll, fcntl ...`

## Features
### standard IRC commands:
-   `/JOIN <channel>` - Join a specified channel.
-   `/PART <channel>` - Leave a specified channel.
-   `/NICK <nickname>` - Change your nickname.
-   `/WHOIS <nickname>` - Get information about a specified user.
-   `/PRIVMSG <nickname/channel> <message>` - Send a private message to a specified user or channel.
-   `/NOTICE <user>` - Send a private message that will not be publicly displayed.
-   `/KICK <channel> <user>` - Kick a specified user from the channel.
-   `/TOPIC <channel> <topic>` - Change the topic of the specified channel.
-   `/INVITE <user>` - Invite a user to join the channel.
-   `/MODE <channel> <mode>` - Modify the modes of a specified channel.

### Mode (change the channel/user mode):
-   `i`: Set/remove Invite-only channel.
-   `t`: Set/remove the restrictions of the TOPIC command to channel operators.
-   `k`: Set/remove the channel key (password).
-   `o`: Give/take channel operator privilege.
-   `l`: Set/remove the user limit to the channel.

## Prerequisites:

-   C++ compiler
-   client IRC: `irssi 1.2.3`

***irssi installation***
**macOS**: `brew install irssi`

**linux**: `sudo apt install irssi`

**source code**: https://github.com/irssi/irssi.git

## Installation Steps:

1.  Clone the project repository: `git clone https://github.com/Jud42/ft_IRC.git`
2.  Navigate to the project directory: `cd ft_IRC`
3.  Compile the source code: `make`
4.  Run the ft_IRC server: `./ircserv <port> <the connexion password>`
> password: The connection password. It will be needed by any IRC client that tries to connect to your server.

## connexion
1. Run the IRC client: `irssi`
2. Command: `/connect <server address> pass <password>`
