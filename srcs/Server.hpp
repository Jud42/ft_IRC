#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <cstdlib>  // (exit)


class	Server 
{

	public:
		//pub_constructor{
		Server( const char * port, const char *pass);
		~Server( void );
		void run ( void );

    private:

};
#endif