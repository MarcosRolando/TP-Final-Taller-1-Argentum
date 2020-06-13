#ifndef ARGENTUM_FONT_H
#define ARGENTUM_FONT_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

#include "SDLException.h"

class Font {
private:
    TTF_Font *font;
public:
    Font(const std::string& path, int fontSize);
    TTF_Font* getFont();
    ~Font();
};


#endif //ARGENTUM_FONT_H
