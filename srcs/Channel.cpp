#include "Channel.hpp"


// **********************************************************************************************
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

// **********************************************************************************************
Channel::~Channel ()
{

}

// **********************************************************************************************
const std::string Channel::getChannelName (void)
{
    return(this->_name);
}

// **********************************************************************************************
const std::string Channel::getChannelMode (void)
{
    return(this->_mode);
}

// **********************************************************************************************
const std::map <std::string, std::string> Channel::getMapUsers (void)
{
    return (this->_channelClients); 
}

// **********************************************************************************************
const std::string Channel::getConnectedUsers (void)
{

    std::string result = "";
    // pass thrugh all Users, the banned users are not listead
	std::map<std::string, std::string>::iterator it(this->_channelClients.begin());
    for ( ; it != this->_channelClients.end() ; it++)
    {
        // check mode, pos 0 #, pos 1 mode
        std::string combo = it->second;
        // avoid banned users
        if (combo.substr(0,1) != "b")
        {
            if (combo.substr(0,2) == "O#")
                result += " #";
            else
                result += " ";
            result += it->first;   
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

// **********************************************************************************************
const std::string Channel::getConnectedUsersMode (std::string const nickname)
{
    (void) nickname;
    if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -------------------------------
	{
	 	std::cout << BLU;
        std::cout << "[ CHANNEL::getConnectedUsersMode ]" <<  std::endl;
        std::cout << "  nickname :" << nickname << std::endl;
	 	std::cout << NOC;
	} // --------------------------------------------------------------------------------------  

    std::string result = "";
    // pass through all Users, the banned users are not listead
    std::map<std::string, std::string>::iterator it(this->_channelClients.begin());
    for ( ; it != this->_channelClients.end() ; it++)
    {
        if (it->first == nickname)
        {
            result = it->second;
            break;
        }
    }

    if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -------------------------------
	{
	 	std::cout << BLU;
        std::cout << "  result :" << result << std::endl;
	 	std::cout << NOC;
	} // --------------------------------------------------------------------------------------
    return (result);
}

// **********************************************************************************************
int Channel::getNbUsers (void)
{
    int result = 0;
    // pass thrugh all Users, the banned users are not conted
	std::map<std::string, std::string>::iterator it(this->_channelClients.begin());
    for ( ; it != this->_channelClients.end() ; it++)
    {
        // check mode, pos 0 mode, pos 1 #
        std::string combo = it->second;
        // avoid banned users
        if (combo.substr(0,1) != "b")
        {
            result += 1;
        }
    }
    return (result);
}

// **********************************************************************************************
void Channel::setChannelMode (const std::string User, const std::string channelMode)
{
        // Structure of channelMode
        // pos 0 = mode = [O, o, i , b, ....]
        // pos 1 = Owner of the channel = "#"

        // find if the User that is already defined
		std::map<std::string, std::string>::iterator it = _channelClients.find(User);

		// insert a new newUser
		if (it != _channelClients.end())
		{
			//	Update the set into the _channelClients map
            it->second = channelMode;
		}
}

// **********************************************************************************************
int Channel::setChannelUserMode (const std::string User, const std::string channelMode)
{
        // Structure of channelMode
        // pos 0 = mode = [O, o, i , b, ....]
        // pos 1 = Owner of the channel = "#"

        // find if the User that is already defined
		std::map<std::string, std::string>::iterator it = _channelClients.find(User);

		// insert a new newUser
		if (it != _channelClients.end())
		{
			//	Update the set into the _channelClients map
            it->second = channelMode;
			return 1;
		}
		return 0;
}


// **********************************************************************************************
void Channel::setConnectedUser (const std::string newUser) 
{
        // find if the newUser is already defined
		std::map<std::string, std::string>::iterator it = _channelClients.find(newUser);

		// insert a new newUser
		if (it == _channelClients.end())
		{
			//	Create a new set into the _channelClients map
			this->_channelClients.insert(std::pair<std::string, std::string>(newUser, "o"));
		}
}
// **********************************************************************************************
void Channel::resetConnectedUser (const std::string removedUser)
{
        // find if the newUser is already defined
		std::map<std::string, std::string>::iterator it = _channelClients.find(removedUser);

		// delete the User
		if (it != _channelClients.end())
		{
			//	Delete the set into the _channelClients map
			this->_channelClients.erase (it);
		}
}
