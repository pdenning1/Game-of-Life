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

	_boardViewport.x = BOARD_X;
	_boardViewport.y = BOARD_Y;
	_boardViewport.w = BOARD_WIDTH;
	_boardViewport.h = BOARD_HEIGHT;

	_mouseEventX = 0;
	_mouseEventY = 0;
	_changeCell = false;

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
		if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
		{
			//Get mouse position
			int x, y;
			SDL_GetMouseState( &x, &y );

			//Check if mouse is in button
			bool inside = true;

			//Mouse is left of the button
			if( x < BOARD_X )
			{
				inside = false;
			}
			//Mouse is right of the button
			else if( x > BOARD_X + BOARD_WIDTH )
			{
				inside = false;
			}
			//Mouse above the button
			else if( y < BOARD_Y )
			{
				inside = false;
			}
			//Mouse below the button
			else if( y > BOARD_Y + BOARD_HEIGHT )
			{
				inside = false;
			}

			//Mouse is outside button
			if( !inside )
			{
				// handle other buttons here?
			}
			//Mouse is inside button
			else
			{
				//Set mouse over sprite
				switch( e.type )
				{
					case SDL_MOUSEMOTION:
						// handle cell selection here
						std::cout << "Mouse moving over board" << std::endl;
						std::cout << "X: " << x << "     Y: " << y << std::endl;
						break;
					
					case SDL_MOUSEBUTTONDOWN:
						// handle mouse pressed here		
						std::cout << "Mouse pressed" << std::endl;
						std::cout << "X: " << x << "     Y: " << y << std::endl;
						break;
					
					case SDL_MOUSEBUTTONUP:
						// handle mouse released here		
						std::cout << "Mouse released" << std::endl;
						std::cout << "X: " << x << "     Y: " << y << std::endl;
						_eventQueue.push_back(GAME_EVENT_CELL_CHANGE);
						_changeCell = true;
						break;
				}

				float xpercent = x - BOARD_X;
				xpercent = xpercent / BOARD_WIDTH;
				_mouseEventX = xpercent * SCREEN_WIDTH * 0.7; // TODO - figure out source of .7 factor...

				float ypercent = y - BOARD_Y;
				ypercent = ypercent / BOARD_HEIGHT;
				_mouseEventY = ypercent * SCREEN_HEIGHT * 0.7;
				

				// _mouseEventX = ((x - BOARD_X) / BOARD_WIDTH) * SCREEN_WIDTH;
				// _mouseEventY = ((y - BOARD_Y) / BOARD_HEIGHT) * SCREEN_HEIGHT;
				std::cout << "boardX: " << _mouseEventX << "     boardY: " << _mouseEventY << std::endl;



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
	int cellWidth = SCREEN_WIDTH / 25;
	int cellHeight = SCREEN_WIDTH / 25;
	int cellGap = cellWidth / 10;

	int boardWidth = board->GetWidth();
	int boardHeight = board->GetHeight();

	SDL_RenderSetViewport( _renderer, &_boardViewport );

	//Clear screen
	//SDL_SetRenderDrawColor( _renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	//SDL_RenderClear( _renderer );

	for (int i = 0; i < boardWidth; i++)
	{
		for ( int j = 0; j < boardHeight; j++)
		{
			int xPos = (cellWidth + cellGap) * i; 
			int yPos = (cellHeight + cellGap) * j;
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

			if(!board->GetState(i,j))
			{
				//Render grey filled quad
				SDL_Rect fillRect = { xPos, yPos, cellWidth, cellHeight };
				SDL_SetRenderDrawColor( _renderer, 0x96, 0x96, 0x96, 0xFF );		
				SDL_RenderFillRect( _renderer, &fillRect );
			}
			else
			{
				//Render red filled quad
				SDL_Rect fillRect = { xPos, yPos, cellWidth, cellHeight };
				SDL_SetRenderDrawColor( _renderer, 0x84, 0x02, 0x10, 0xFF );		
				SDL_RenderFillRect( _renderer, &fillRect );
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




	// //Render red filled quad
	// SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	// SDL_SetRenderDrawColor( _renderer, 0xFF, 0x00, 0x00, 0xFF );		
	// SDL_RenderFillRect( _renderer, &fillRect );

	
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