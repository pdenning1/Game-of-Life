#include <iostream>
#include <vector>
#include <memory>

//


// project includes
#include "GameManager.h"




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

    return 0;
}