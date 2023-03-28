#include "ConfigFile.hpp"

// to use this modules, the file to load is expecting having the hereafter formating
//  value lines must not hold spaces around values and use a = as separator
//  if # on position 0 fill declare the line as commentary

ConfigFile::ConfigFile (std::string fileName): _fileName(fileName)
{
    // loading of config file
	std::fstream inputFile;

	
    inputFile.open(this->_fileName.c_str());

    // ensure the file is existing
    if (!inputFile.is_open())
    {
		std::cerr << RED << "Error: file " << this->_fileName << " not found." << NOC << std::endl;
	}
	else
    // loading values
	{

    	std::string line;
        std::string rightPart, leftPart;
        unsigned int positionEQ;
        while (getline(inputFile, line))
        {
            // find the first # --> comments
            positionEQ = line.find("#");
            // avoid comment lines
            if (positionEQ != 0)
            {
            // find the first = to determine validity of the line
                positionEQ = line.find("=");
                if (positionEQ < line.length())
                {
                    leftPart = line.substr(0, positionEQ);
                    rightPart = line.substr(positionEQ + 1, line.length() - (positionEQ + 1));
                    //std::cout << "|" << leftPart << "|" << rightPart << "|"<< std::endl;

                    this->_values.insert(std::pair <std::string, std::string> (leftPart, rightPart));
                    
                }
            }
        
        }
    }
    inputFile.close();
}



ConfigFile::~ConfigFile (void) 
{
    return;
}

// -- Private -------------------------------------------------------------------------------------------

ConfigFile::ConfigFile (void) 
{
    return;
}

ConfigFile::ConfigFile (const ConfigFile &src)
{
    *this = src;
}
ConfigFile &ConfigFile::operator=(const ConfigFile &rhs)
{
    if (this != &rhs)
    {
        this->_values = rhs._values;
        this->_fileName = rhs._fileName;
    }
    return (*this);
}

// -- Public ---------------------------------------------------------------------------------------------


std::string ConfigFile::getConfigValue(const std::string key)
{
    // search the passed key related value
    std::multimap<std::string, std::string>::iterator it = this->_values.lower_bound(key);

    // ensure the value is found
    std::string returnedValue = "";
    if (it->first == key)
        returnedValue = it->second;

    return (returnedValue);
}
    

