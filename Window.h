//
// Created by ivan on 7/6/20.
//

#ifndef ARGENTUM_WINDOW_H
#define ARGENTUM_WINDOW_H

#include <SDL.h>

class Window {
private:
    SDL_Window* window;

public:
    Window();
    ~Window();

};


#endif //ARGENTUM_WINDOW_H
