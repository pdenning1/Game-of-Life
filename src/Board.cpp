#include "Board.h"


Board::Board(int width, int height)
{
    for(int i = 0; i < width; i++)
    {
        std::vector<bool> col;
        _board.push_back(col);

        for(int j = 0; j < height; j++)
        {
            _board[i].push_back(false);
        }
    }

    for(int i = 0; i < width; i++)
    {
        std::vector<bool> col;
        _nextBoard.push_back(col);

        for(int j = 0; j < height; j++)
        {
            _nextBoard[i].push_back(false);
        }
    }

    _width = width;
    _height = height;

    _xOffset = width / 2;
    _yOffset = height / 2;
}

int Board::GetWidth()
{
    return _width;
}

int Board::GetHeight()
{
    return _height;
}