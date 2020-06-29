//
// Created by ivan on 7/6/20.
//

#include "Font.h"

Font::Font(const std::string& path, int fontSize) {
    //load media
    font = TTF_OpenFont(path.c_str(), fontSize);
    if(font == NULL ){
        throw TPException("Failed to load lazy font! SDL_ttf Error: %s\n",
                          TTF_GetError() );
    }
}

TTF_Font *Font::getFont() {
    return this->font;
}

Font::~Font() {
    TTF_CloseFont(font);
}