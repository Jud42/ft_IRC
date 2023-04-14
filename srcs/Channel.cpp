#include "Channel.hpp"


Channel::Channel () 
{

}

Channel::Channel (std::string name) : _name(name)
{

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
        
int Channel::getNbConnection (void)
{
    int resultat = 0;
    
    std::map<std::string, char>::iterator it;
    for (it = _usage.begin(); it != _usage.end(); ++it) 
    {
        resultat += 1;
    }
    return(resultat);
}

std::string Channel::getConnectedUsers (void)
{
    return ("[YO] [vroch]");
}

int Channel::setChannelMode (char)
{
    return ('i');
}

int Channel::setConnectedUser (std::string)
{
    return (1);
}