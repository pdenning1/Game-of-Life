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

    //Frees media and shuts down SDL
    void closeWindow();

    void handleEvents();
    bool isEvents();
    GAME_EVENTS getNextEvent();

    void DrawBoard(Board* board);
    void DrawFrame();

    ////
    void TestTexture();

private:
    SDL_Surface* loadSurface( std::string path );
    SDL_Texture* loadTexture( std::string path );

    bool addEvent(GAME_EVENTS event);
    void addButton(int x, int y, int width, int height, GAME_EVENTS event);

    //The window we'll be rendering to
    SDL_Window* _window = NULL;
    SDL_Renderer* _renderer = NULL;
        
    //The surface contained by the window
    SDL_Surface* _screenSurface = NULL;

    //The image we will load and show on the screen
    SDL_Surface* _helloWorld = NULL;

    SDL_Surface* _currentSurface = NULL;

    //SDL_Rect _boardViewport;

    std::vector<GAME_EVENTS> _eventQueue; 

    float _mouseEventX;
    float _mouseEventY;
    bool _changeCell;

    std::vector<Button*> _buttons;
};