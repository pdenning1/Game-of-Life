#pragma once

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Coordinates.h"

const std::string saveFileName{"savefile.txt"};


class SaveFileManager
{
public:
    std::vector<Coordinates>* loadSavedLayout();
    bool saveBoardLayout(std::vector<Coordinates>* boardLayout);
};