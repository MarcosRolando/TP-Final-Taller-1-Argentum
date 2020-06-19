//
// Created by ivan on 18/6/20.
//

#include "Minichat.h"

Minichat::Minichat(Font& font, SDL_Renderer& renderer) : input(font,
        renderer), renderer(renderer) {
    focusOnMinichat = false;
}

void Minichat::handleEvent(SDL_Event &e) {
//If mouse event happened
    if( e.type == SDL_MOUSEBUTTONDOWN )
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );

        //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if( x < mPosition.x )
        {
            inside = false;
        }
            //Mouse is right of the button
        else if( x > mPosition.x + DEFAULT_MINICHAT_WIDTH )
        {
            inside = false;
        }
            //Mouse above the button
        else if( y < mPosition.y )
        {
            inside = false;
        }
            //Mouse below the button
        else if( y > mPosition.y + DEFAULT_MINICHAT_HEIGHT )
        {
            inside = false;
        }

        focusOnMinichat = inside;
    }
    else if( e.type == SDL_TEXTINPUT )
    {
        if (focusOnMinichat){
            std::string newInput = e.text.text;
            input.appendText(newInput);
        }
    }
}

void Minichat::inputText(std::string& newInput){
    input.appendText(newInput);
}

bool Minichat::isFocused(){
    return focusOnMinichat;
}

void Minichat::render(){
    input.render(0,0, SDL_Color{0xFF,0xFF,0xFF,0xFF});
}

Minichat::~Minichat() {

}


