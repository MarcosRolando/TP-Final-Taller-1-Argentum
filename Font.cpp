//
// Created by ivan on 7/6/20.
//

#include "Font.h"

Font::Font() {
//Initialize SDL_ttf
    if( TTF_Init() == -1 ){//ver si esto va en la clase SDL gral
        throw SDLException("SDL_ttf could not initialize! SDL_ttf Error:"
                           " %s\n", TTF_GetError() );
    }

    //load media
    font = TTF_OpenFont("../lazy.ttf", 28 );
    if(font == NULL ){
        throw SDLException("Failed to load lazy font! SDL_ttf Error: %s\n",
                TTF_GetError() );
    }
}

Font::~Font() {
    TTF_CloseFont(font);
    TTF_Quit();//ver si esto va en la clase SDL gral
}

TTF_Font *Font::getFont() {
    return this->font;
}
