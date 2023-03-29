#ifndef TO_STR
#define TO_STR

#include <iostream>
#include <sstream>

template <class T>
std::string	to_str( T to_convert)
{
	std::stringstream ss;
	ss << to_convert;
	return(ss.str());
}

#endif