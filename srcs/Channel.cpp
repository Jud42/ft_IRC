#include "Channel.hpp"


// **********************************************************************************************
// constructor of the channel
Channel::Channel (std::string name, ConfigFile *IRCconfig): _name(name), _IRCconfig(IRCconfig)
{

     if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -----------------------------
	{
	 	std::cout << BLU;
        std::cout << "[ CHANNEL::channel ] Constructor" <<  std::endl;
        std::cout << " _name :" << this->_name << std::endl;
	 	std::cout << NOC;
	} // --------------------------------------------------------------------------------------
}

// **********************************************************************************************
// destructor of the channel
Channel::~Channel ()
{
     if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -----------------------------
	{
	 	std::cout << BLU;
        std::cout << "[ CHANNEL::channel ] Destructor" <<  std::endl;
        std::cout << " _name :" << this->_name << std::endl;
	 	std::cout << NOC;
	} // --------------------------------------------------------------------------------------
}

// **********************************************************************************************
// return the name of the channel hold by this channel object
const std::string Channel::getChannelName (void)
{
    if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -----------------------------
	{
	 	std::cout << BLU;
        std::cout << "[ CHANNEL::channel ] getChannelName" <<  std::endl;
        std::cout << " _name :" << this->_name << std::endl;
	 	std::cout << NOC;
	} // --------------------------------------------------------------------------------------
    return(this->_name);
}

// **********************************************************************************************
// return the channel's mode
const std::string Channel::getChannelMode (void)
{
    if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -----------------------------
	{
	 	std::cout << BLU;
        std::cout << "[ CHANNEL::channel ] getChannelMode" <<  std::endl;
        std::cout << " _name :" << this->_name << std::endl;
        std::cout << " _mode :" << this->_mode << std::endl;
	 	std::cout << NOC;
	} // --------------------------------------------------------------------------------------
    return(this->_mode);
}

// **********************************************************************************************
// return the map including all user's FD and their respective mode/ownership (when not banned!)
const std::map <int, std::string> Channel::getChannelFDsModeMap (void)
{
    if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -----------------------------
	{
	 	std::cout << BLU;
        std::cout << "[ CHANNEL::channel ] getChannelFDsModeMap" <<  std::endl;
	 	std::cout << NOC;
	} // --------------------------------------------------------------------------------------
    std::map<int, std::string> result;
    std::map<int, std::string>::iterator it(this->_channel_FD_Mode.begin());
    for ( ; it != this->_channel_FD_Mode.end() ; it++)
    {
        // check mode, pos 0 #, pos 1 mode
        std::string combo = it->second;
        // avoid banned users
        if (combo.substr(0,1) != "b")
        {
			result.insert(std::pair<int, std::string>(it->first, it->second));
            if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -----------------------------
            {
                std::cout << BLU;
                std::cout << " FD & Mode :" << it->first << " " << it->second << std::endl;
                std::cout << NOC;
            } // --------------------------------------------------------------------------------------            
        }
    }
    return (result);
}

int Channel::getChannelConnectedFD (const int fd)
{


    int result = 0;
    std::map<int, std::string>::const_iterator it(this->_channel_FD_Mode.find(fd));

    if (it != this->_channel_FD_Mode.end())
        result = it->first;

    if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -----------------------------
	{
	 	std::cout << BLU;
        std::cout << "[ CHANNEL::channel ] getChannelConnectedFD" <<  std::endl;
        std::cout << " result :" << result << std::endl;
	 	std::cout << NOC;
	} // --------------------------------------------------------------------------------------

    return (result);
}

const std::string Channel::getChannelConnectedFDMode (const int fd)
{
    std::string result = "";
    std::map<int, std::string>::const_iterator it(this->_channel_FD_Mode.find(fd));

    if (it != this->_channel_FD_Mode.end())
        result = it->second;

    if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -----------------------------
	{
	 	std::cout << BLU;
        std::cout << "[ CHANNEL::channel ] getChannelConnectedFDMode" <<  std::endl;
        std::cout << " mode found :" << result << std::endl;
	 	std::cout << NOC;
	} // --------------------------------------------------------------------------------------    

    return (result);
}

// **********************************************************************************************
int Channel::getNbUsers (void)
{
    if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -----------------------------
	{
	 	std::cout << BLU;
        std::cout << "[ CHANNEL::channel ] getNbUsers" <<  std::endl;
        std::cout << " _name :" << this->_name << std::endl;
	 	std::cout << NOC;
	} // --------------------------------------------------------------------------------------
    int result = 0;
    // pass thrugh all Users, the banned users are not conted
	std::map<int, std::string>::iterator it(this->_channel_FD_Mode.begin());
    for ( ; it != this->_channel_FD_Mode.end() ; it++)
    {
        // check mode, pos 0 mode, pos 1 @
        std::string combo = it->second;
        // avoid banned users
        if (combo.substr(0,1) != "b")
        {
            result += 1;
            if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -----------------------------
            {
                std::cout << BLU;
                std::cout << " FD :" << it->first << std::endl;
                std::cout << NOC;
            } // --------------------------------------------------------------------------------------            
        }
    }
         if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -----------------------------
	{
	 	std::cout << BLU;
        std::cout << " result :" << result << std::endl;
	 	std::cout << NOC;
	} // --------------------------------------------------------------------------------------
    return (result);
}

// ***********************************************************************************************
void Channel::setChannelFDMode (const int fd, const std::string channelMode)
{
    std::map<int, std::string>::const_iterator it(this->_channel_FD_Mode.find(fd));
    if (it != this->_channel_FD_Mode.end())
        this->_channel_FD_Mode.at(fd) = channelMode;
    if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -----------------------------
	{
	 	std::cout << BLU;
        std::cout << "[ CHANNEL::channel ] setChannelFDMode" <<  std::endl;
        std::cout << " mode set :" << it->second << std::endl;
	 	std::cout << NOC;
	} // -------------------------------------------------------------------------------------- 
}


// ***********************************************************************************************
// Update the user mode with a return of status
int Channel::setChannelUserMode (const int FD, const std::string channelMode)
{
        int result = 0;
        // Structure of channelMode
        // pos 0 = mode = [O, o, i , b, ....]
        // pos 1 = Owner of the channel = "#"

        // find if the User that is already defined
		std::map<int, std::string>::iterator it = this->_channel_FD_Mode.find(FD);

		// insert a new newUser
		if (it != this->_channel_FD_Mode.end())
		{
			//	Update the set into the _channelClients map
            it->second = channelMode;
			result = 1;
		}

    if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -----------------------------
	{
	 	std::cout << BLU;
        std::cout << "[ CHANNEL::channel ] setChannelUserMode" <<  std::endl;
        std::cout << " mode set :" << it->second << std::endl;
        std::cout << " return value :" << result << std::endl;
	 	std::cout << NOC;
	} // --------------------------------------------------------------------------------------    
    return (result);     
}

// ***********************************************************************************************
// insert the user (through the FD identification) to the given channel
void Channel::setChannelConnectedFD (const int newFD) 
{
        // find if the newFD is already defined
		std::map<int, std::string>::const_iterator it = this->_channel_FD_Mode.find(newFD);

		if (it == this->_channel_FD_Mode.end())
		{
			//	Create a new set into the _channelClients map, with default mode
			this->_channel_FD_Mode.insert(std::pair<int, std::string>(newFD, "o"));
		}

    if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -----------------------------
	{
	 	std::cout << BLU;
        std::cout << "[ CHANNEL::channel ] setChannelConnectedFD" <<  std::endl;
        std::map<int, std::string>::const_iterator it = this->_channel_FD_Mode.find(newFD);
        std::cout << " FD set :" << it->first << std::endl;
        std::cout << " Mode set :" << it->second << std::endl;
	 	std::cout << NOC;
	} // -------------------------------------------------------------------------------------- 
}


// ***********************************************************************************************
// Erase the user (through the FD identification) to the given channel
void Channel::resetChannelConnectedFD (const int removedFD)
{
        // check if the removedFD is already defined
		std::map<int, std::string>::iterator it = this->_channel_FD_Mode.find(removedFD);

		
		if (it != this->_channel_FD_Mode.end())
		{ 
			//	delete the set into the _channel_FD_Mode map
			this->_channel_FD_Mode.erase(removedFD);
		}
    if ("DEBUG" == this->_IRCconfig->getConfigValue("DEBUG")) // -----------------------------
	{
	 	std::cout << BLU;
        std::cout << "[ CHANNEL::channel ] resetChannelConnectedFD" <<  std::endl;
        std::cout << " FD removed :" << removedFD << std::endl;
        it = this->_channel_FD_Mode.begin();
        for ( ; it != this->_channel_FD_Mode.end() ; it++)
            std::cout << " FD still alive :" << it->first << std::endl; 

	 	std::cout << NOC;
	} // --------------------------------------------------------------------------------------         
}
