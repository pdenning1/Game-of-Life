#pragma once

#include <cstdio>
#include <iostream>
#include <SDL2/SDL.h>

// project includes
#include "Constants.h"



class Button
{

public:
    Button();
    Button(int x, int y, int width, int height, GAME_EVENTS event);

    bool checkForPress(int mouseX, int mouseY);
    GAME_EVENTS getEvent() { return _clickEvent; }

    void render(SDL_Renderer* renderer);

private:
    int _xPosition;
    int _yPosition;
    int _width;
    int _height;

    GAME_EVENTS _clickEvent;


};