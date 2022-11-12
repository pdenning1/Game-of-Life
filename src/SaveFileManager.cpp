#include "SaveFileManager.h"


std::string SaveFileManager::loadBoardLayout()
{
    std::string json = "";

    std::ifstream filestream(saveFileName);
    if (filestream.is_open())
    {
        while (std::getline(filestream, json))
        {
            std::cout << json << std::endl;
        }
    }

    return json;
}