#pragma once

#include <iostream>


#include "SDLManager.h"
#include "SaveFileManager.h"
#include "Board.h"
#include "Constants.h"


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


private:
    void iterateBoard();

    SDLManager* _sdlManager;
    SaveFileManager* _saveFileManager;

    Board* _currentBoard;
    Board* _nextBoard;

    bool _sdlInitialized;
    bool _quit;
    bool _running;


};