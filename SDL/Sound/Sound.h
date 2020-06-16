//
// Created by ivan on 10/6/20.
//

#ifndef ARGENTUM_SOUND_H
#define ARGENTUM_SOUND_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>

#include "../TPException.h"

class Sound {
private:
    Mix_Chunk* sound;
public:
    explicit Sound(std::string path);
    Mix_Chunk* getSound();
    ~Sound();
};


#endif //ARGENTUM_SOUND_H
