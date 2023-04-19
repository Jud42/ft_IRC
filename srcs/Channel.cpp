#include "Channel.hpp"


Channel::Channel (std::string name)
{
    std::cout << "name :" << name << std::endl;
    this->_name = name;
    // if ("DEBUG" == _IRCconfig->getConfigValue("DEBUG")) // -------------------------------------
	// {
	// 	// retrieve error code of getaddrinfo command 
	//  	std::cout << BLU;
    //     std::cout << "[ Channel::channel ]" <<  std::endl;
    //     std::cout << "_name :" << this->_name << std::endl;
	//  	std::cout << NOC;
	// } // --------------------------------------------------------------------------------------
}
        
       
Channel::~Channel ()
{
    
}

std::string Channel::getChannelName (void)
{
    return(this->_name);
}

char Channel::getChannelMode (void)
{
    return(this->_mode);
}

char Channel::getUserMode (void)
{
    // find the pair in _channel_client and retireve the 
    return(this->_mode);
}
        
int Channel::getNbConnection (void)
{
    int resultat = 0;
    
    

    {
        resultat += 1;
    }
    return(resultat);
}

std::string Channel::getConnectedUsers (void)
{
    return ("vroch\n\rD1vroch\n\r");
}

void Channel::setChannelMode (char)
{
    
}

void Channel::setConnectedUser (std::string NewUser)
{
    // Ensure the user is not already defined

    // Add the user and the default mode
    //     if ("DEBUG" == _IRCconfig->getConfigValue("DEBUG")) // -------------------------------------
	// {
	// 	// retrieve error code of getaddrinfo command 
	//  	std::cout << BLU;
    //     std::cout << "[ Channel::setConnectedUser ]" <<  std::endl;
    //     std::cout << "NewUser :" << NewUser << std::endl;
	//  	std::cout << NOC;
	// } // --------------------------------------------------------------------------------------

    _channelClients.insert ( std::pair<std::string, char>(NewUser, 'O'));

}