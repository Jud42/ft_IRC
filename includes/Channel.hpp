#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "define.hpp"
# include <iostream>
# include "ConfigFile.hpp"

class Channel
{
public:

        Channel (std::string name, ConfigFile *IRCconfig);
        ~Channel ();

        const std::string getChannelName (void);
        const std::string getChannelMode (void);

        // will be discarded
        // const std::map <std::string, std::string> getMapUsers (void);
        // const std::string getConnectedUsers (void);
        // const std::string getConnectedUsersMode (const std::string nickname);

        // and replaced by
        const std::map <int, std::string>       getChannelFDsModeMap (void);
        int                                     getChannelConnectedFD (const int fd); // confirm FD is linked to the channel
        const std::string                       getChannelConnectedFDMode (const int fd);


        int getNbUsers (void);
        
        // will be discarded
        //void setChannelMode (const std::string user, const std::string channelMode);
        //int setChannelUserMode (const std::string user, const std::string channelMode);
        //void setConnectedUser (const std::string newUser);
        //void resetConnectedUser (const std::string removeUser);

        // and replace by
        void    setChannelFDMode (const int fd, const std::string channelMode);
        int     setChannelUserMode (const int fd, const std::string channelMode);
        void    setChannelConnectedFD (const int newFD);

        void    resetChannelConnectedFD (const int removeFD);

private:

        std::string                            _name; // channel's name
        std::string                            _mode; // channel's mode
        // will be discarded
        std::map <std::string, std::string>    _channelClients; // User & mode (mode[o, O, b, i] + owner=#)
        // and replace by
        std::map <int, std::string>            _channel_FD_Mode; // FD & mode related to the channel (mode[o, O, b, i] + owner=#)
        ConfigFile		               *_IRCconfig;

     

};

#endif
