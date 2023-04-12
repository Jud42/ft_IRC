#ifndef CONFIG_FILE_HPP
#define CONFIG_FILE_HPP



#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "define.hpp"

class ConfigFile
{

    public:
        ConfigFile (std::string FileName);
        ~ConfigFile (void);
        std::string getConfigValue (std::string const key);


    private:
        ConfigFile (void);
        ConfigFile (const ConfigFile &src);
        ConfigFile &operator=(const ConfigFile &rhs);

        std::string _fileName;
        std::multimap <std::string, std::string> _values;

};

#endif
