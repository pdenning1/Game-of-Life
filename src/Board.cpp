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

std::vector<Coordinates>* Board::getBoardLayout()
{
    std::vector<Coordinates>* boardLayout = new std::vector<Coordinates>();
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (_board[i][j])
            {
                Coordinates coord;
                coord.x = i - _xOffset;
                coord.y = j - _yOffset;

                boardLayout->push_back(coord);
            }
        }
    }

    return boardLayout;
}

void Board::loadBoardLayout(std::vector<Coordinates>* layout)
{
    for (auto coord : *layout)
    {
        if (((coord.x + _xOffset) < _width) && ((coord.y + _yOffset) < _height))
        {
            _board[coord.x + _xOffset][coord.y + _yOffset] = true;
        }
    }
}
