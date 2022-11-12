#include "SaveFileManager.h"


std::string SaveFileManager::loadBoardLayout()
{
    std::string json = "";
    std::string line;

    std::ifstream filestream(saveFileName);
    if (filestream.is_open())
    {
        while (std::getline(filestream, line))
        {
            json += line;
            std::cout << json << std::endl;
        }

        if (json.compare("") != 0)
        {
            // parse json here
        }
    }

    return json;
}