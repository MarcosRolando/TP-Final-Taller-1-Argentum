//
// Created by ivan on 7/6/20.
//

#include "Renderer.h"

Renderer::Renderer(SDL_Window* window) {
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

    if( renderer == NULL ){
        throw SDLException("Renderer could not be created! SDL Error:"
                           " %s\n", SDL_GetError());
    }
}

Renderer::~Renderer() {
    SDL_DestroyRenderer( renderer );
}

SDL_Renderer *Renderer::getRenderer() {
    return this->renderer;
}
