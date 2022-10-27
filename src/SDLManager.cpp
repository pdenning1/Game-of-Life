#include "SDLManager.h"


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
	int cellWidth = SCREEN_WIDTH / 20;
	int cellHeight = SCREEN_WIDTH / 20;
	int cellGap = cellWidth / 10;

	int boardWidth = board->GetWidth();
	int boardHeight = board->GetHeight();

	//Clear screen
	SDL_SetRenderDrawColor( _renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( _renderer );

	for (int i = 0; i < boardWidth; i++)
	{
		int xPos = (cellWidth + cellGap) * i; 

		//Render black filled quad
		SDL_Rect fillRect = { xPos, SCREEN_HEIGHT / 4, cellWidth, cellHeight };
		SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );		
		SDL_RenderFillRect( _renderer, &fillRect );
	}



	// //Render red filled quad
	// SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	// SDL_SetRenderDrawColor( _renderer, 0xFF, 0x00, 0x00, 0xFF );		
	// SDL_RenderFillRect( _renderer, &fillRect );

	// //Render green outlined quad
	// SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
	// SDL_SetRenderDrawColor( _renderer, 0x00, 0xFF, 0x00, 0xFF );		
	// SDL_RenderDrawRect( _renderer, &outlineRect );
	
	// //Draw blue horizontal line
	// SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0xFF, 0xFF );		
	// SDL_RenderDrawLine( _renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );

	// //Draw vertical line of yellow dots
	// SDL_SetRenderDrawColor( _renderer, 0xFF, 0xFF, 0x00, 0xFF );
	// for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
	// {
	// 	SDL_RenderDrawPoint( _renderer, SCREEN_WIDTH / 2, i );
	// }

	//Update screen
	SDL_RenderPresent( _renderer );
	
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