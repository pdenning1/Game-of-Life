#pragma once

#include <vector>
#include <iostream>


class Board
{

public:
    Board(int width, int height);

    int GetWidth();
    int GetHeight();

private:
    std::vector<std::vector<bool>> _board;
    int _xOffset;
    int _yOffset;
    int _width;
    int _height;

};