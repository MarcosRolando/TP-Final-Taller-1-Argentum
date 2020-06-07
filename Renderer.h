//
// Created by ivan on 7/6/20.
//

#ifndef ARGENTUM_RENDERER_H
#define ARGENTUM_RENDERER_H

#include <SDL.h>
#include <SDL_image.h>
#include "SDLException.h"

class Renderer {
private:
    SDL_Renderer* renderer;

public:
    explicit Renderer(SDL_Window* window);
    SDL_Renderer* getRenderer();
    ~Renderer();

};


#endif //ARGENTUM_RENDERER_H
