#include <string>
#include <iostream>
#include "define.hpp"
#include "Server.hpp"




std::string find_cmd_arg(std::string buffer, std::string command)
{
	// std::cout << YEL << " find_cmd_arg" << NOC << std::endl;
	// print_all_caractere(buffer);
	size_t pos_start = buffer.find(command); // find first occurency of hte command
	if (pos_start == std::string::npos) // if not found - npos represents an invalid or not-found position
		throw Server::CmdException();
	if (pos_start != 0)
	{
		if (buffer[pos_start - 1] != '\n')
		{
			// return ("");
			std::cout << command;
			throw Server::CmdException();
		}
	}
	pos_start += command.size() + 1;
	std::string cleanCmd = buffer.substr(pos_start);
	size_t pos_end = cleanCmd.find("\r\n"); // find first occurency of "\r\n"
	if (pos_end != std::string::npos) // if found
		cleanCmd = cleanCmd.substr(0, pos_end); // extract the string until there
	// std::cout << YEL << "-" << cleanCmd << "-" << NOC << std::endl;
	return (cleanCmd);
}
