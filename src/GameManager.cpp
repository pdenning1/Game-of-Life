#include "GameManager.h"



GameManager::GameManager()
{
    _quit = false;
    _running = false;
    _sdlInitialized = false;

    _currentBoard = new Board(20,20); // TODO - sort sizing...
    _nextBoard = nullptr;

    _sdlManager = new SDLManager();

    std::cout << "Starting Game..." << std::endl;

}

GameManager::~GameManager()
{
    std::cout << "Ending Game..." << std::endl;

    if(_currentBoard != nullptr)
    {
        delete _currentBoard;
        _currentBoard = nullptr;
    }

    if(_nextBoard != nullptr)
    {
        delete _nextBoard;
        _nextBoard = nullptr;
    }

    if(_sdlManager != nullptr)
    {
        _sdlManager->closeWindow();

        delete _sdlManager;
        _sdlManager = nullptr;
    }
}

bool GameManager::init()
{
    _sdlManager = new SDLManager();

    //Start up SDL and create window
	if( !_sdlManager->init() )
	{
        _sdlInitialized = false;
		std::cout <<  "Failed to initialize SDLManager" << std::endl;
	}
	else
	{
        _sdlInitialized = true;
		std::cout <<  "Initialized SDLManager" << std::endl;
    }

	_sdlManager->DrawFrame(); // render the graphics that won't change thoughout the game (background etc)

    return _sdlInitialized;

}

bool GameManager::handleInput()
{
    
    _sdlManager->handleEvents(); // tell the sdlManager to process any SDL_events

    
    if (_sdlManager->isEvents()) // any sdl_events that trigger game_events are handled by the GameManager heres
    {
        GAME_EVENTS event = _sdlManager->getNextEvent();

        if (event == GAME_EVENT_QUIT)
        {
            _quit = true;
        }

        else if (event == GAME_EVENT_CELL_CHANGE)
        {
            
        }

        else if (event == GAME_EVENT_RUN)
        {
            _running = !_running;
        }

    }

    return _quit;
}

void GameManager::updateGameState()
{
    // update state
    if (_running)
    {
        _currentBoard->Iterate();

        SDL_Delay(750); // TODO - implement timer / threading so that ui remains responsive

    }
}

void GameManager::render()
{
    _sdlManager->DrawBoard(_currentBoard, 60);
}