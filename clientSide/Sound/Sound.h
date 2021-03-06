//
// Created by ivan on 10/6/20.
//

#ifndef ARGENTUM_SOUND_H
#define ARGENTUM_SOUND_H

#include <SDL_mixer.h>
#include <string>

#include "../../libs/TPException.h"

class Sound {
private:
    Mix_Chunk* sound;
public:
    explicit Sound(const std::string& path);
    Sound(const Sound&) = delete;
    Sound& operator=(const Sound&) = delete;

    /* Devuelve el sonido */
    Mix_Chunk* getSound();


    ~Sound();
};


#endif //ARGENTUM_SOUND_H
