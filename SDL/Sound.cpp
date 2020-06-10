//
// Created by ivan on 10/6/20.
//

#include "Sound.h"

Sound::Sound(std::string path) {
    sound = Mix_LoadWAV(path.c_str());
    if(sound == NULL ){
        throw SDLException("Failed to load sound effect! SDL_mixer "
                           "Error: %s\n",Mix_GetError() );
    }
}

/*void Sound::loadFromFile(std::string path){

}*/

Sound::~Sound() {
    Mix_FreeChunk(sound);
}

Mix_Chunk *Sound::getSound() {
    return sound;
}
