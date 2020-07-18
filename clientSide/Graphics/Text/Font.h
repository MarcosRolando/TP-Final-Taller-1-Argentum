#ifndef ARGENTUM_FONT_H
#define ARGENTUM_FONT_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

#include "../../../libs/TPException.h"

class Font {
private:
    TTF_Font *font;
public:
    /* Constructor */
    Font(const std::string& path, int fontSize);
    TTF_Font* getFont();
    /* Destructor */
    ~Font();

};


#endif //ARGENTUM_FONT_H
