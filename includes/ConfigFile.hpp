#ifndef CONFIG_FILE_HPP
#define CONFIG_FILE_HPP

#define		RED	"\033[31;1m"
#define		GRE	"\033[32;1m"
#define		YEL	"\033[33;1m"
#define		BLU	"\033[34;1m"
#define		NOC "\033[0m"

#include <iostream>
#include <fstream>
#include <map>
#include <string>

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