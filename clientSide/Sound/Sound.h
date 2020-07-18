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
    /* Constructor */
    explicit Sound(std::string path);
    /* Devuelve el sonido */
    Mix_Chunk* getSound();
    /* Destructor */
    ~Sound();
};


#endif //ARGENTUM_SOUND_H
