//
// Created by ivan on 10/6/20.
//

#include "Sound.h"

Sound::Sound(std::string path) {
    sound = Mix_LoadWAV(path.c_str());
    if(sound == nullptr) {
        throw TPException("Failed to load sound effect! SDL_mixer "
                           "Error: %s\n", Mix_GetError() );
    }
}

Mix_Chunk *Sound::getSound() {
    return sound;
}

Sound::~Sound() {
    Mix_FreeChunk(sound);
}


