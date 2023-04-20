#include "Channel.hpp"



Channel::Channel (std::string name, ConfigFile *IRCconfig): _name(name), _IRCconfig(IRCconfig)
{
    (void) _IRCconfig;
     if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -------------------------------
	{
	 	std::cout << BLU;
        std::cout << "[ CHANNEL::channel ]" <<  std::endl;
        std::cout << " _name :" << this->_name << std::endl;
	 	std::cout << NOC;
	} // --------------------------------------------------------------------------------------
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
    std::string result = "@ ";
    // pass thrugh all Users, the banned users are not listead
	std::map<std::string, std::string>::iterator it = _channelClients.begin();
    for ( ; it != _channelClients.end() ; it++)
    {
        // check mode, pos 0 #, pos 1 mode
        std::string combo = it->second;
        // avoid banned users
        if (combo.substr(1,1) != "b")
        {
            if (combo.substr(0,1) == "#")
                result += combo.substr(0,1);
            result += it->first;
            result += " ";
        }
    }

    if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -------------------------------
	{
	 	std::cout << BLU;
        std::cout << "[ CHANNEL::getConnectedUsers ]" <<  std::endl;
        std::cout << " result :" << result << std::endl;
	 	std::cout << NOC;
	} // --------------------------------------------------------------------------------------
    return (result);
}

void Channel::setChannelMode (const std::string User, const std::string channelMode)
{
    (void) User;
    (void) channelMode;
}

void Channel::setConnectedUser (const std::string NewUser) 
{
    (void) NewUser;
    // Ensure the user is not already defined

    // Add the user and the default mode

        if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // ------------------------------
	    {
	 	std::cout << BLU;
        std::cout << "[ CHANNEL::setConnectedUser ]" <<  std::endl;
        std::cout << "NewUser :" << NewUser << std::endl;
	 	std::cout << NOC;
	    } // --------------------------------------------------------------------------------------

        // find if the newUser is already defined
		std::map<std::string, std::string>::iterator it = _channelClients.find(NewUser);
		// insert a new newUser
		if (it == _channelClients.end())
		{
			//	Create a new set into the _channelClients map
			this->_channelClients.insert(std::pair<std::string, std::string>(NewUser, "o"));

		}


}

const std::map <std::string, std::string> Channel::getMapUsers (void)
{
    return (this->_channelClients); 
}
