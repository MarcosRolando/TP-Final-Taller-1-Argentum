//
// Created by ivan on 10/6/20.
//

#ifndef ARGENTUM_SOUND_H
#define ARGENTUM_SOUND_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>

#include "SDLException.h"

class Sound {
private:
    Mix_Chunk* sound;
public:
    Sound(std::string path);
    Mix_Chunk* getSound();
    ~Sound();

    //void loadFromFile(std::string path);
};


#endif //ARGENTUM_SOUND_H
