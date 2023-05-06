#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "define.hpp"
# include <iostream>
# include <vector>
# include "ConfigFile.hpp"

class Channel
{
public:

        Channel (std::string name, ConfigFile *IRCconfig);
        ~Channel ();

        const std::string                       getChannelName (void);
        const std::string                       getChannelMode (void);


        const std::map <int, std::string>       getChannelFDsModeMap (void);
        int                                     getChannelConnectedFD (const int fd); // confirm FD is linked to the channel
        const std::string                       getChannelConnectedFDMode (const int fd);


        int                                     getNbUsers (void);
        const std::string                       getTopic (void);
        bool                                    checkChannelInvite(const int fd);
       	void									setChannelMode(const std::string & new_mode); 
        void                                    setChannelFDMode (const int fd, const std::string channelMode);
        int                                     setChannelUserMode (const int fd, const std::string channelMode);
        void                                    setChannelConnectedFD (const int newFD);
        void                                    setChannelTopic (const std::string message);
        void                                    setChannelInvite (const int fd);

        void                                    resetChannelConnectedFD (const int removeFD);

private:

        std::string                            _name; // channel's name
        std::string                            _mode; // channel's mode
        std::string                            _topic; // channel's topic

        std::map <int, std::string>            _channel_FD_Mode; // FD & mode related to the channel (mode[o, O, b, i] + owner=#)
        std::vector <int>                      _invite; // for FD that were invited


        // for debug
        ConfigFile		               *_IRCconfig;


     

};

#endif
