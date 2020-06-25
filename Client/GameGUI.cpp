//
// Created by marcos on 6/25/20.
//

#include "GameGUI.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

void GameGUI::setMapSize(int rows, int columns) {
    map.setSize(rows, columns);
}

GameGUI::GameGUI() : repo(screen.getRenderer()), map(repo, camera),
                    minichat(screen.getRenderer()){
    _initializeSDL();
}

GameGUI::~GameGUI() {
    IMG_Quit();
    SDL_Quit();
}

void GameGUI::_initializeSDL() {
    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw TPException("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    } else {
        //Set texture filtering to linear
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "MipmapLinearNearest")) {
            std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
        }
        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if(!(IMG_Init(imgFlags) & imgFlags)) {
            throw TPException("SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
        }
    }
}
