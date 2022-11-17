#include "GameManager.h"



GameManager::GameManager()
{
    _quit = false;
    _running = false;
    _sdlInitialized = false;

    _boardSize = MEDIUM;
    _currentBoard = new Board(BOARDWIDTH_MED, BOARDHEIGHT_MED);
    _nextBoard = nullptr;

    _sdlManager = new SDLManager();
    _saveFileManager = new SaveFileManager();

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

    std::vector<Coordinates>* boardCoords = _saveFileManager->loadSavedLayout();

    for(auto coord : *boardCoords)
    {
        std::cout << coord.x << " " << coord.y << std::endl;
    }

    _currentBoard->loadBoardLayout(boardCoords);

    return _sdlInitialized;

}

bool GameManager::handleInput()
{
    
    _sdlManager->handleEvents(); // tell the sdlManager to process any SDL_events

    
    if (_sdlManager->isEvents()) // any sdl_events that trigger game_events are handled by the GameManager here
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

        else if (event == GAME_EVENT_INCREASESIZE)
        {
            increaseBoardSize();
            _sdlManager->DrawBoard(_currentBoard);
        }

        else if (event == GAME_EVENT_DECREASESIZE)
        {
            decreaseBoardSize();
            _sdlManager->DrawBoard(_currentBoard);
        }

    }

    return _quit;
}

void GameManager::updateGameState()
{
    // update state
    if (_running)
    {
        this->iterateBoard();

        SDL_Delay(750); // TODO - implement timer / threading so that ui remains responsive
    }
}

void GameManager::render()
{
    _sdlManager->DrawBoard(_currentBoard);
}


void GameManager::iterateBoard()
{
    int width = _currentBoard->GetWidth();
    int height = _currentBoard->GetHeight();
    _nextBoard = new Board(width, height);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (((i > 0) && (i < width-1)) && ((j > 0) && (j < height-1))) // ignore edges for now.... TODO
            {
                int sum = 0;
                for (int x = i -1; x <= i + 1; x++)
                {
                    for (int y = j - 1; y <= j + 1; y++)
                    {
                        if(_currentBoard->GetCellState(x, y))
                        {
                            sum++;
                        }
                    }
                }

                if(_currentBoard->GetCellState(i, j)) // if cell is populated
                {
                    sum--; // subtract 1 for current cell
                    if(sum <= 1 || sum >= 4)
                    {
                        _nextBoard->SetCellState(i, j, false);
                    }
                    else
                    {
                        _nextBoard->SetCellState(i, j, true);
                    }
                }
                else // if cell is empty
                {
                    if(sum == 3)
                    {
                        _nextBoard->SetCellState(i, j, true);
                    }
                }
            }
        }
    }

    delete _currentBoard;
    _currentBoard = _nextBoard;
    _nextBoard = nullptr;
}

bool GameManager::saveGameState()
{
    return _saveFileManager->saveBoardLayout(_currentBoard->getBoardLayout());
}

void GameManager::increaseBoardSize()
{
    if (_boardSize == SMALL)
    {
        _boardSize = MEDIUM;
        std::vector<Coordinates>* layout = _currentBoard->getBoardLayout();
        delete _currentBoard;
        _currentBoard = new Board(BOARDWIDTH_MED, BOARDHEIGHT_MED);
        _currentBoard->loadBoardLayout(layout);
        delete layout;
    }
    else if (_boardSize == MEDIUM)
    {
        _boardSize = LARGE;
        std::vector<Coordinates>* layout = _currentBoard->getBoardLayout();
        delete _currentBoard;
        _currentBoard = new Board(BOARDWIDTH_LARGE, BOARDHEIGHT_LARGE);
        _currentBoard->loadBoardLayout(layout);
        delete layout;
    }
}

void GameManager::decreaseBoardSize()
{
    if (_boardSize == LARGE)
    {
        _boardSize = MEDIUM;
        std::vector<Coordinates>* layout = _currentBoard->getBoardLayout();
        delete _currentBoard;
        _currentBoard = new Board(BOARDWIDTH_MED, BOARDHEIGHT_MED);
        _currentBoard->loadBoardLayout(layout);
        delete layout;
    }
    else if (_boardSize == MEDIUM)
    {
        _boardSize = SMALL;
        std::vector<Coordinates>* layout = _currentBoard->getBoardLayout();
        delete _currentBoard;
        _currentBoard = new Board(BOARDWIDTH_SMALL, BOARDHEIGHT_SMALL);
        _currentBoard->loadBoardLayout(layout);
        delete layout;
    }
}