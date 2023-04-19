#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "define.hpp"
# include "ConfigFile.hpp"

class Channel
{
public:

        Channel (std::string name);
        ~Channel ();

        std::string getChannelName (void);
        char getChannelMode (void);
        char getUserMode (void);
        int getNbConnection (void);
        std::string getConnectedUsers (void);

        void setChannelMode (char);
        void setConnectedUser (std::string);

private:

        std::string                     _name;
        char                            _mode;
        std::map <std::string, char>    _channelClients;
        //ConfigFile		*	_IRCconfig;
     
};

#endif