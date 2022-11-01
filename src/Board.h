#pragma once

#include <vector>
#include <iostream>


class Board
{

public:
    Board(int width, int height);

    int GetWidth();
    int GetHeight();

    bool GetState(int i, int j) { return _board[i][j]; }
    void ChangeCell( int i, int j) { _board[i][j] = !_board[i][j]; }

private:
    std::vector<std::vector<bool>> _board;
    int _xOffset;
    int _yOffset;
    int _width;
    int _height;

};