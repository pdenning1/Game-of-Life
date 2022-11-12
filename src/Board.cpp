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

void Board::Iterate()
{
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (((i > 0) && (i < _width-1)) && ((j > 0) && (j < _height-1))) // ignore edges for now.... TODO
            {
                if(i == 4 && j == 4) // TODO - remove this
                {
                    std::cout << "stop here \n";
                }

                int sum = 0;
                for (int x = i -1; x <= i + 1; x++)
                {
                    for (int y = j - 1; y <= j + 1; y++)
                    {
                        if(_board[x][y])
                        {
                            sum++;
                        }
                    }
                }

                if(_board[i][j]) // if cell is populated
                {
                    sum--; // subtract 1 for current cell
                    if(sum <= 1 || sum >= 4)
                    {
                        _nextBoard[i][j] = false;
                    }
                    else
                    {
                        _nextBoard[i][j] = true;
                    }
                }
                else // if cell is empty
                {
                    if(sum == 3)
                    {
                        _nextBoard[i][j] = true;
                    }
                }
            }
        }
    }

    for(int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            _board[i][j] = _nextBoard[i][j];
        }
    }
}

int Board::GetWidth()
{
    return _width;
}

int Board::GetHeight()
{
    return _height;
}