//
// Created by ivan on 7/6/20.
//

#include "Window.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


Window::Window() {
    window = SDL_CreateWindow("Argentum",SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );

    if (window == nullptr){
        throw SDLException("Window could not be created! SDL Error: %s\n",
                SDL_GetError());
    }

    width = SCREEN_WIDTH;
    height = SCREEN_HEIGHT;
}

Window::~Window() {
    if (window != nullptr){//Capaz nno hace falta este chequeo
        SDL_DestroyWindow(window);
    }

}

SDL_Window *Window::getWindow() {
    return this->window;
}


