#include "SoundRepository.h"
#include <unistd.h>

#define QUEUE_SIZE 3

SoundRepository::SoundRepository() {
    _loadSounds();
    _loadMusic();
}

void SoundRepository::_loadSounds(){
    try {
        sounds.emplace(SwordAttack, "../../clientSide/Sounds/swordAttack.wav");
        sounds.emplace(HeavyAttack, "../../clientSide/Sounds/HeavyAttack.wav");
        sounds.emplace(Attack, "../../clientSide/Sounds/genericAttack.wav");
        sounds.emplace(Attack2, "../../clientSide/Sounds/genericAttack2.wav");
        sounds.emplace(Arrow, "../../clientSide/Sounds/arrow.wav");
        sounds.emplace(Death, "../../clientSide/Sounds/Death.wav");
        sounds.emplace(Death1, "../../clientSide/Sounds/YodaDeath.wav");
        sounds.emplace(Step, "../../clientSide/Sounds/Step.wav");
        sounds.emplace(Explotion1, "../../clientSide/Sounds/Explotion1.wav");
        sounds.emplace(Explotion2, "../../clientSide/Sounds/Explotion2.wav");
        sounds.emplace(Explotion3, "../../clientSide/Sounds/Explotion3.wav");
        sounds.emplace(Healing, "../../clientSide/Sounds/heal.wav");

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    Mix_Volume(-1, 25);
}

void SoundRepository::_loadMusic(){
    music = Mix_LoadMUS("../../clientSide/Sounds/argentumOnlineOST.mp3");
    Mix_VolumeMusic(20);
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
