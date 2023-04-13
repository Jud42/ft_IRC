#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "define.hpp"
# include "Server.hpp"

class Channel
{
public:

        Channel ();
        Channel (std::string name);
        ~Channel ();

        std::string getChannelName (void);
        char getChannelMode (void);
        int getNbConnection (void);
        std::string getConnectedUsers (void);

        int setChannelMode (char);
        int setConnectedUser (std::string);





private:

        std::string                     _name;
        char                            _mode;
        std::map <std::string, char>    _usage;

       
};

#endif