#pragma once

#include <vector>
#include <iostream>

#include "Coordinates.h"


class Board
{

public:
    Board(int width, int height);

    int GetWidth();
    int GetHeight();

    bool GetCellState(int i, int j) { return _board[i][j]; }
    void SetCellState( int i, int j, bool state) { _board[i][j] = state; }
    void ChangeCell(int i, int j) { _board[i][j] = !_board[i][j]; }

    std::vector<Coordinates>* getBoardLayout();
    void loadBoardLayout(std::vector<Coordinates>* layout);

private:
    std::vector<std::vector<bool>> _board;
    std::vector<std::vector<bool>> _nextBoard;

    int _xOffset;
    int _yOffset;
    int _width;
    int _height;

};