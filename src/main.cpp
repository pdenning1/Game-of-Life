#include <iostream>

// project includes
#include "GameManager.h"

#include "SaveFileManager.h"


int main() {

	GameManager theGameManager;
	bool quit = false;

	theGameManager.init();

	///////////////
	SaveFileManager save;
	save.loadBoardLayout();

	//////////////


	while(!quit)
	{
		quit = theGameManager.handleInput();

		theGameManager.updateGameState();

		theGameManager.render();

	}

    return 0;
}