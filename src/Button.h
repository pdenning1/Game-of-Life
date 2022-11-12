#pragma once

#include <cstdio>
#include <iostream>
#include <SDL2/SDL.h>

// project includes




class Button
{

public:
    Button();
    Button(int x, int y, int width, int height);

    bool checkForPress(int mouseX, int mouseY);

    void render(SDL_Renderer* renderer);

private:
    int _xPosition;
    int _yPosition;
    int _width;
    int _height;


};