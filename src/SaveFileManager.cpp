#include "SaveFileManager.h"

/// @brief Load the board from savefile.txt in the build folder. NOTE: for now this function assumes the savefile is in perfect format
/// @return 
std::vector<Coordinates>* SaveFileManager::loadSavedLayout()
{
    std::string json = "";
    std::string line;
    std::vector<Coordinates> *coords = new std::vector<Coordinates>();
    std::string x;
    std::string y;

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
            std::replace(json.begin(), json.end(), '[', ' ');
            std::replace(json.begin(), json.end(), ']', ' ');
            std::replace(json.begin(), json.end(), ',', ' ');

            std::istringstream jsonStream(json);
            while (jsonStream >> x >> y)
            {
                Coordinates coord;
                coord.x = stoi(x);
                coord.y = stoi(y);
                coords->push_back(coord);
            }
        }
    }

    return coords;
}

/// @brief Save the current board layout as a json array in savefile.txt
/// @param boardLayout 
/// @return Save successful or not
bool SaveFileManager::saveBoardLayout(std::vector<Coordinates>* boardLayout)
{
    int numCoords = boardLayout->size();

    std::ostringstream jsonStream;
    jsonStream <<  "[";

    for (int i = 0; i < numCoords; i++)
    {
        jsonStream << "[" << boardLayout->at(i).x << "," << boardLayout->at(i).y <<  "]";

        if (i < numCoords)
        {
            jsonStream << ",";
        }
    }

    std::ofstream filestream;
    filestream.open("savefile.txt", std::ofstream::out | std::ofstream::trunc);
    if (filestream.is_open())
    {
        filestream << jsonStream.str();

        return true;
    }

    return false;
}