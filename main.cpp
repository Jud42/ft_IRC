#include <iostream>

int main (int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Require ./" << argv[0] << " <PORT> <PASSWORD>" << std::endl;
    }
}