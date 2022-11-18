#include <cstdio>
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>


// project includes
#include "Constants.h"
#include "Board.h"
#include "Button.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

const int BOARD_X = SCREEN_WIDTH / 7;
const int BOARD_Y = SCREEN_HEIGHT / 7;
const int BOARD_WIDTH = (SCREEN_WIDTH / 7) * 5;
const int BOARD_HEIGHT = (SCREEN_HEIGHT / 7) * 5;

class SDLManager
{
public:
    SDLManager() { std::cout << "Creating SDLManager" << std::endl; }
    ~SDLManager();
    //Starts up SDL and creates window
    bool init();

    //Loads media
    bool loadMedia();

    void handleEvents();
    bool isEvents();
    GAME_EVENTS getNextEvent();

    void drawBoard(Board* board);
    void drawFrame();

private:
    SDL_Texture* loadTexture( std::string path );

    bool addEvent(GAME_EVENTS event);
    void addButton(int x, int y, int width, int height, GAME_EVENTS event, SDL_Texture* texture);

    //Frees media and shuts down SDL
    void closeWindow();

    //The window we'll be rendering to
    SDL_Window* _window = NULL;
    SDL_Renderer* _renderer = NULL;        

    std::vector<GAME_EVENTS> _eventQueue; 

    float _mouseEventX;
    float _mouseEventY;
    bool _changeCell;

    std::vector<Button*> _buttons;
};