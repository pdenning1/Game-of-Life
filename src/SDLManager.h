#include <cstdio>
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>


// project includes
#include "Constants.h"
#include "Board.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

class SDLManager
{
public:
    SDLManager() { std::cout << "Creating SDLManager" << std::endl; }
    ~SDLManager() { std::cout << "Destroying SDLManager" << std::endl; }
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

private:
    SDL_Surface* loadSurface( std::string path );

    bool addEvent(GAME_EVENTS event);

    //The window we'll be rendering to
    SDL_Window* _window = NULL;
    SDL_Renderer* _renderer = NULL;
        
    //The surface contained by the window
    SDL_Surface* _screenSurface = NULL;

    //The image we will load and show on the screen
    SDL_Surface* _helloWorld = NULL;

    SDL_Surface* _currentSurface = NULL;

    std::vector<GAME_EVENTS> _eventQueue; 
};