#include "SDLManager.h"



SDLManager::~SDLManager()
{ 
	std::cout << "Destroying SDLManager" << std::endl; 
	for (auto button : _buttons)
	{
		delete button;
	}
}

bool SDLManager::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		_window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( _window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			_screenSurface = SDL_GetWindowSurface( _window );

			_renderer = SDL_CreateRenderer( _window, -1, SDL_RENDERER_ACCELERATED );
			if( _renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
		}
	}

	_mouseEventX = 0;
	_mouseEventY = 0;
	_changeCell = false;

	addButton(20,20,50,50, GAME_EVENT_QUIT);

	addButton(400, 30, 50, 50, GAME_EVENT_INCREASESIZE);
	addButton(500, 30, 50, 50, GAME_EVENT_DECREASESIZE);
	addButton((SCREEN_WIDTH / 2) - 20, BOARD_Y + BOARD_HEIGHT + 50, 100, 50, GAME_EVENT_RUN);

	return success;
}

void SDLManager::handleEvents()
{
	//Event handler
	SDL_Event e;

	//Handle events on queue
	while( SDL_PollEvent( &e ) != 0 )
	{
		//User requests quit
		if( e.type == SDL_QUIT )
		{
			_eventQueue.push_back(GAME_EVENT_QUIT);
		}

		//User presses a key
		else if( e.type == SDL_KEYDOWN )
		{
			//Select surfaces based on key press
			switch( e.key.keysym.sym )
			{
				case SDLK_UP:
				_eventQueue.push_back(GAME_EVENT_K_UP);
				break;

				case SDLK_DOWN:
				_eventQueue.push_back(GAME_EVENT_K_DOWN);
				break;
			}
		}

			//If mouse event happened
		if( e.type == SDL_MOUSEBUTTONUP )
		{
			//Get mouse position
			int x, y;
			SDL_GetMouseState( &x, &y );

			for (auto button : _buttons)
			{
				if(button->checkForPress(x,y))
				{
					_eventQueue.push_back(button->getEvent());

				}
			}

			//Check if mouse is in board
			bool inside = true;

			//Mouse is left of the board
			if( x < BOARD_X )
			{
				inside = false;
			}
			//Mouse is right of the board
			else if( x > BOARD_X + BOARD_WIDTH )
			{
				inside = false;
			}
			//Mouse above the board
			else if( y < BOARD_Y )
			{
				inside = false;
			}
			//Mouse below the board
			else if( y > BOARD_Y + BOARD_HEIGHT )
			{
				inside = false;
			}

			//Mouse is inside board
			if( inside )
			{
				_eventQueue.push_back(GAME_EVENT_CELL_CHANGE);
				_changeCell = true;

				_mouseEventX = x;
				_mouseEventY = y;
			}
		}
		else if (e.type == SDL_MOUSEMOTION)
		{
			int x, y;
			SDL_GetMouseState( &x, &y );

			_mouseEventX = x;
			_mouseEventY = y;
		}

	}
}

bool SDLManager::isEvents()
{
	return _eventQueue.size() > 0;
}

GAME_EVENTS SDLManager::getNextEvent()
{
	if (_eventQueue.size() > 0)
	{
		GAME_EVENTS event = _eventQueue[0];
		_eventQueue.erase(_eventQueue.begin());
		return event;
	}

	return GAME_EVENT_NO_EVENT;
	 
}

void SDLManager::DrawBoard(Board* board)
{
	int boardWidth = board->GetWidth();
	int boardHeight = board->GetHeight();

	int cellGap = (BOARD_WIDTH / boardWidth) / 10;
	int cellWidth = (BOARD_WIDTH / boardWidth) - cellGap;
	int cellHeight = (BOARD_HEIGHT / boardHeight) - cellGap;
	

	//Clear board
	SDL_Rect fillRect = { BOARD_X, BOARD_Y, BOARD_WIDTH, BOARD_HEIGHT };
	SDL_SetRenderDrawColor( _renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderFillRect( _renderer, &fillRect );

	int startingX = (BOARD_X + (BOARD_WIDTH - (boardWidth * (cellWidth + cellGap))) / 2);
	int startingY = (BOARD_Y + (BOARD_HEIGHT - (boardHeight * (cellHeight + cellGap))) / 2);

	for (int i = 0; i < boardWidth; i++)
	{
		for ( int j = 0; j < boardHeight; j++)
		{
			int xPos = startingX + ((cellWidth + cellGap) * i); 
			int yPos = startingY + ((cellHeight + cellGap) * j);
			bool mouseOver = false;

			if (_mouseEventX > xPos)
			{
				if (_mouseEventX < (xPos + cellWidth))
				{
					if (_mouseEventY > yPos)
					{
						if (_mouseEventY < (yPos + cellHeight))
						{
							mouseOver = true;

							if (_changeCell)
							{
								_changeCell = false;
								board->ChangeCell(i,j);
							}
						}
					}
				}
			}

			if(!board->GetCellState(i,j))
			{
				//Render grey filled quad
				SDL_Rect cellRect = { xPos, yPos, cellWidth, cellHeight };
				SDL_SetRenderDrawColor( _renderer, 0x96, 0x96, 0x96, 0xFF );		
				SDL_RenderFillRect( _renderer, &cellRect );
			}
			else
			{
				//Render red filled quad
				SDL_Rect cellRect = { xPos, yPos, cellWidth, cellHeight };
				SDL_SetRenderDrawColor( _renderer, 0x84, 0x02, 0x10, 0xFF );		
				SDL_RenderFillRect( _renderer, &cellRect );
			}

			if(mouseOver)
			{
				// Highlight cell
				SDL_Rect outlineRect = { xPos - cellGap, yPos - cellGap, cellWidth + (2*cellGap), cellHeight + (2*cellGap) };
				SDL_SetRenderDrawColor( _renderer, 0x84, 0x02, 0x10, 0xFF );		
				SDL_RenderDrawRect( _renderer, &outlineRect );
			}
			else
			{
				// clear highlight from previous mouseover
				SDL_Rect outlineRect = { xPos - cellGap, yPos - cellGap, cellWidth + (2*cellGap), cellHeight + (2*cellGap) };
				SDL_SetRenderDrawColor( _renderer, 0xFF, 0xFF, 0xFF, 0xFF );		
				SDL_RenderDrawRect( _renderer, &outlineRect );
			}
		}
	}

	//Update screen
	SDL_RenderPresent( _renderer );	
}

void SDLManager::addButton(int x, int y, int width, int height, GAME_EVENTS event)
{
	Button* button = new Button(x, y, width, height, event);
	_buttons.push_back(button);
}

void SDLManager::DrawFrame()
{
	//Clear screen
	SDL_SetRenderDrawColor( _renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( _renderer );

	//Render green outlined quad
	SDL_Rect outlineRect = { BOARD_X - 10, BOARD_Y - 10, BOARD_WIDTH + 20, BOARD_HEIGHT + 20 };
	SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0x00 );		
	SDL_RenderDrawRect( _renderer, &outlineRect );

	//Update screen
	SDL_RenderPresent( _renderer );

	for(auto button : _buttons)
	{
		button->render(_renderer);
	}
}


bool SDLManager::loadMedia()
{
	//Loading success flag
	bool success = true;
	SDL_Surface* otherWorld = loadSurface( "hello_otherWorld.bmp" );

	//Load splash image
	_helloWorld = loadSurface( "hello_world.bmp" );
	if( _helloWorld == NULL )
	{
		success = false;
	}
    else
    {
		//Main loop flag
			bool quit = false;

			_currentSurface = _helloWorld;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//User presses a key
                    else if( e.type == SDL_KEYDOWN )
                    {
                        //Select surfaces based on key press
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_UP:
                            _currentSurface = otherWorld;
                            break;

                            case SDLK_DOWN:
                            _currentSurface = _helloWorld;
                            break;
						}
					}
				}

				//Apply the image
				SDL_BlitSurface( _currentSurface, NULL, _screenSurface, NULL );
				
				//Update the surface
				SDL_UpdateWindowSurface( _window );
			}
    }

	return success;
}

SDL_Surface* SDLManager::loadSurface( std::string path )
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }
		else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface( loadedSurface, _screenSurface->format, 0 );
		if( optimizedSurface == NULL )
		{
			printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

    return optimizedSurface;
}

SDL_Texture* SDLManager::loadTexture( std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( _renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

void SDLManager::closeWindow()
{
	//Deallocate surface
	SDL_FreeSurface( _helloWorld );
	_helloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow( _window );
	_window = NULL;

	SDL_DestroyRenderer( _renderer );
	_renderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

void SDLManager::TestTexture()
{
	bool quit = false;
	SDL_Event e;
	SDL_Texture* gTexture = loadTexture("hello_world.bmp");


		//While application is running
	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
		}

		//Clear screen
		SDL_RenderClear( _renderer );

		//Render texture to screen
		SDL_RenderCopy( _renderer, gTexture, NULL, NULL );

		//Update screen
		SDL_RenderPresent( _renderer );
	}
}