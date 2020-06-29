#include "SoundRepository.h"
#include <unistd.h>

#define QUEUE_SIZE 3

SoundRepository::SoundRepository() {
    _loadSounds();
    _loadMusic();
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
    Mix_FreeMusic(music);
}

Mix_Music* SoundRepository::getMusic() {
    return music;
}

Mix_Chunk* SoundRepository::getSound(SoundID id) {
    return sounds.at(id).getSound();
}
