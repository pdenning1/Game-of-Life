#pragma once

#include <iostream>


#include "SDLManager.h"
#include "SaveFileManager.h"
#include "Board.h"
#include "Constants.h"


const int BOARDWIDTH_SMALL = 24;
const int BOARDHEIGHT_SMALL = 16;
const int BOARDWIDTH_MED = 48;
const int BOARDHEIGHT_MED = 32;
const int BOARDWIDTH_LARGE = 96;
const int BOARDHEIGHT_LARGE = 64;

enum BoardSize
{
    SMALL,
    MEDIUM,
    LARGE
};


/// @brief Class to drive the main game loop and handle all of the game logic
class GameManager
{

public:
    GameManager();
    ~GameManager();

    bool init();

    bool handleInput();
    void updateGameState();
    void render();

    bool saveGameState();


private:
    void iterateBoard();
    void increaseBoardSize();
    void decreaseBoardSize();

    SDLManager* _sdlManager;
    SaveFileManager* _saveFileManager;

    Board* _currentBoard;
    Board* _nextBoard;
    
    BoardSize _boardSize;

    bool _sdlInitialized;
    bool _quit;
    bool _running;
};