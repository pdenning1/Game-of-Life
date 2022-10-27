#include <iostream>
#include <vector>
#include <memory>

//


// project includes
#include "test1.h"
#include "SDLManager.h"


int main() {
    std::cout << "Hello World!" << "\n";

    Test test1(5);

    test1.TestPrint();

    SDLManager* sdlManager = new SDLManager();

    	//Start up SDL and create window
	if( !sdlManager->init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		// if( !sdlManager->loadMedia() )
		// {
		// 	printf( "Failed to load media!\n" );
		// }
		bool quit = false;
		Board* board = new Board(10,10);

		while(!quit)
		{
			sdlManager->DrawBoard(board);

			sdlManager->handleEvents();
			if (sdlManager->isEvents())
			{
				GAME_EVENTS event = sdlManager->getNextEvent();

				if (event == GAME_EVENT_QUIT)
				{
					quit = true;
				}

			}
		}
		delete board;
    }

    sdlManager->closeWindow();

    delete sdlManager;

    return 0;
}