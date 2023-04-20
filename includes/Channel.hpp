#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "define.hpp"
# include <iostream>
# include <map>
# include "ConfigFile.hpp"



class Channel
{
public:

        Channel (std::string name, ConfigFile *IRCconfig);
        ~Channel ();

        const std::string getChannelName (void);
        const std::string getChannelMode (void);
        const std::map <std::string, std::string> getMapUsers (void);
        const std::string getConnectedUsers (void);
        

        void setChannelMode (const std::string User, const std::string channelMode);
        void setConnectedUser (const std::string NewUser);

private:

        std::string                            _name;
        std::string                            _mode;
        std::map <std::string, std::string>    _channelClients; // Nick & mode
        ConfigFile		               *_IRCconfig;

     

};

#endif
