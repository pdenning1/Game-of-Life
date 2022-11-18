#include "Button.h"


Button::Button()
{
    _xPosition = 0;
    _yPosition = 0;
    _width = 0;
    _height = 0;
    _clickEvent = GAME_EVENT_NO_EVENT;
    _buttonTexture = nullptr;
}

Button::Button(int x, int y, int width, int height, GAME_EVENTS event) :
    _xPosition(x), _yPosition(y), _width(width), _height(height), _clickEvent(event)
{
    _buttonTexture = nullptr;
}

void Button::setTexture(SDL_Texture* texture)
{
    _buttonTexture = texture;
}


bool Button::checkForPress(int mouseX, int mouseY)
{
    return ((mouseX > _xPosition) && (mouseX < (_xPosition + _width)) && (mouseY > _yPosition) && (mouseY < (_yPosition + _height)));
}

void Button::render(SDL_Renderer* renderer)
{
    //Render grey filled quad
    SDL_Rect fillRect = { _xPosition, _yPosition, _width, _height };
    SDL_SetRenderDrawColor( renderer, 0x96, 0x96, 0x96, 0xFF );		
    SDL_RenderFillRect( renderer, &fillRect );


    if (_buttonTexture != nullptr)
    {
        //Set rendering space and render to screen
        SDL_Rect renderQuad = { _xPosition, +_yPosition, _width, _height };
        //Render to screen
        SDL_RenderCopy( renderer, _buttonTexture, NULL, &renderQuad);
    }
    	//Update screen
	SDL_RenderPresent( renderer );
}