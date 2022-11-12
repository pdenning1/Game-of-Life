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

    void Iterate();

private:
    std::vector<std::vector<bool>> _board;
    std::vector<std::vector<bool>> _nextBoard;

    int _xOffset;
    int _yOffset;
    int _width;
    int _height;

};