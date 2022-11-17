#include <iostream>

// project includes
#include "GameManager.h"

#include "SaveFileManager.h"


int main() {

	GameManager theGameManager;
	bool quit = false;

	theGameManager.init();


	while(!quit)
	{
		quit = theGameManager.handleInput();

		theGameManager.updateGameState();

		theGameManager.render();

	}

	theGameManager.saveGameState();

    return 0;
}