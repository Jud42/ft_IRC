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

        std::string getChannelName (void);
        char getChannelMode (void);
        char getUserMode (void);
        int getNbConnection (void);
        std::string getConnectedUsers (void);

        void setChannelMode (const std::string User, const std::string channelMode);
        void setConnectedUser (const std::string NewUser);

private:

        std::string                             _name;
        char                                    _mode;
        std::map <std::string, std::string>    _channelClients;
        ConfigFile		               *_IRCconfig;
     
};

#endif