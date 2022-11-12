#include <iostream>
#include <vector>
#include <memory>

//


// project includes
#include "GameManager.h"




int main() {

	
    // SDLManager* sdlManager = new SDLManager();

    // 	//Start up SDL and create window
	// if( !sdlManager->init() )
	// {
	// 	printf( "Failed to initialize!\n" );
	// }
	// else
	// {
		//Load media
		// if( !sdlManager->loadMedia() )
		// {
		// 	printf( "Failed to load media!\n" );
		// }
		// bool quit = false;
		// bool running = false;
		// Board* board = new Board(20,20);


		//sdlManager->TestTexture();
	GameManager theGameManager;
	bool quit = false;

	theGameManager.init();


		while(!quit)
		{
			
			// // handle input
			// sdlManager->handleEvents();
			// if (sdlManager->isEvents())
			// {
			// 	GAME_EVENTS event = sdlManager->getNextEvent();

			// 	if (event == GAME_EVENT_QUIT)
			// 	{
			// 		quit = true;
			// 	}

			// 	else if (event == GAME_EVENT_CELL_CHANGE)
			// 	{
					
			// 	}

			// 	else if (event == GAME_EVENT_RUN)
			// 	{
			// 		running = !running;
			// 	}

			// }

			quit = theGameManager.handleInput();

			// // update state
			// if (running)
			// {
			// 	board->Iterate();

			// 	SDL_Delay(750); // TODO - implement timer / threading so that ui remains responsive

			// }
			theGameManager.updateGameState();


			// render
			// sdlManager->DrawBoard(board, 60);
			theGameManager.render();

		}
		//delete board;
    //}

    // sdlManager->closeWindow();

    //delete sdlManager;

    return 0;
}