#ifndef LIBF_HPP
# define LIBF_HPP

#include <iostream>
#include <sstream>
#include <string>
#include "define.hpp"

template <class T>
std::string	to_str( T to_convert)
{
	std::stringstream ss;
	ss << to_convert;
	return(ss.str());
}

std::string	extract_cmd(std::string received_msg);
std::string	search_data(std::string src, std::string criteria);

#endif
