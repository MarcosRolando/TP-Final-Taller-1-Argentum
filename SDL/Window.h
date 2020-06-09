//
// Created by ivan on 7/6/20.
//

#ifndef ARGENTUM_WINDOW_H
#define ARGENTUM_WINDOW_H

#include <SDL.h>

#include "SDLException.h"

class Window {
private:
    SDL_Window* window;
    int width;
    int height;

public:
    Window();
    SDL_Window* getWindow();
    ~Window();
    //Agregar los events
};


#endif //ARGENTUM_WINDOW_H
