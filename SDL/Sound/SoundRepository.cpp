#include "SoundRepository.h"
#include <unistd.h>
#define FREQUENCY 44100
#define CHUNKSIZE 2048

#define QUEUE_SIZE 3

SoundRepository::SoundRepository() {
    _init();
    _loadSounds();
    _loadMusic();
}

void SoundRepository::_init() {
    if( SDL_Init(SDL_INIT_AUDIO ) < 0 ) {//Esto iria en una clase SDL general
        throw TPException("SDL could not initialize! SDL Error: %s\n",
                          SDL_GetError() );
    }
    if( Mix_OpenAudio(FREQUENCY, MIX_DEFAULT_FORMAT, 2,
                                                CHUNKSIZE) < 0 ){
        throw TPException("SDL_mixer could not initialize!"
                           " SDL_mixer Error: %s\n", Mix_GetError());
    }
}

void SoundRepository::_loadSounds(){
    try {
        sounds.emplace(Explotion, "../Sounds/explotion.wav");
        sounds.emplace(Attack,"../Sounds/attack.wav");
        sounds.emplace(Punch, "../Sounds/punch.wav");
        sounds.emplace(StepDirt, "../Sounds/stepdirt_1.wav");
    } catch (std::exception& e) {
        std::cout << e.what();
    }
}

void SoundRepository::_loadMusic(){
    music = Mix_LoadMUS("../Sounds/hkost.wav");
    Mix_VolumeMusic(25);
    if(music == NULL ) {
        throw TPException("Failed to load beat music! SDL_mixer Error: "
                           "%s\n", Mix_GetError());
    }
}

SoundRepository::~SoundRepository() {
    //Cierra el mixer
    Mix_FreeMusic( music );
    Mix_Quit();
    SDL_Quit();//Esto iria en la clase SDL general
}

Mix_Music* SoundRepository::getMusic() {
    return music;
}

Mix_Chunk* SoundRepository::getSound(SoundID id) {
    return sounds.at(id).getSound();
}
