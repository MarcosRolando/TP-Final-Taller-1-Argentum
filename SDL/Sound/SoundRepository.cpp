#include "SoundRepository.h"
#include <unistd.h>

#define QUEUE_SIZE 3

SoundRepository::SoundRepository() {
    _loadSounds();
    _loadMusic();
}

void SoundRepository::_loadSounds(){
    try {
        sounds.emplace(SwordAttack, "../Sounds/swordAttack.wav");
        sounds.emplace(HeavyAttack, "../Sounds/HeavyAttack.wav");
        sounds.emplace(Attack, "../Sounds/genericAttack.wav");
        sounds.emplace(Attack2, "../Sounds/genericAttack2.wav");
        sounds.emplace(Arrow, "../Sounds/arrow.wav");
        sounds.emplace(Death, "../Sounds/Death.wav");
        sounds.emplace(Death1, "../Sounds/YodaDeath.wav");
        sounds.emplace(Step, "../Sounds/Step.wav");
        sounds.emplace(Explotion1, "../Sounds/Explotion1.wav");
        sounds.emplace(Explotion2, "../Sounds/Explotion2.wav");
        sounds.emplace(Explotion3, "../Sounds/Explotion3.wav");
        sounds.emplace(Healing, "../Sounds/heal.wav");

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    Mix_Volume(-1, 35);
}

void SoundRepository::_loadMusic(){
    music = Mix_LoadMUS("../Sounds/hkost.wav");
    Mix_VolumeMusic(5);
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
