#include "Button.h"


Button::Button()
{
    _xPosition = 0;
    _yPosition = 0;
    _width = 0;
    _height = 0;
    _clickEvent = GAME_EVENT_NO_EVENT;
}

Button::Button(int x, int y, int width, int height, GAME_EVENTS event) :
    _xPosition(x), _yPosition(y), _width(width), _height(height), _clickEvent(event)
{

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

    	//Update screen
	SDL_RenderPresent( renderer );
}