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
    if(music == NULL ) {
        throw TPException("Failed to load beat music! SDL_mixer Error: "
                           "%s\n", Mix_GetError());
    }
}

/*void SoundRepository::playMusic() {
    if( Mix_PlayingMusic() == 0 ) {//Empieza musica si no habia
        Mix_PlayMusic(music, -1);
    } else if (Mix_PausedMusic() == 1) {//Resume musica si estaba en pausa
        Mix_ResumeMusic();
    }
}

void SoundRepository::pauseMusic() {
    Mix_PauseMusic();
}


void SoundRepository::queueSound(SoundID id) {
    if (soundQueue.size() < QUEUE_SIZE)
        soundQueue.push(id);
}

void SoundRepository::playSounds() {
    Mix_Chunk* soundToPlay;
    long unsigned int queueSize = soundQueue.size();
    for (long unsigned int i = 0; i < queueSize; i++){
        soundToPlay = sounds.at(soundQueue.front()).getSound();
        Mix_PlayChannel(-1, soundToPlay, 0);
        soundQueue.pop();
    }
}*/

SoundRepository::~SoundRepository() {
    //Cierra el mixer
    Mix_Quit();
    SDL_Quit();//Esto iria en la clase SDL general
}

Mix_Music* SoundRepository::getMusic() {
    return music;
}

Mix_Chunk* SoundRepository::getSound(SoundID id) {
    return sounds.at(id).getSound();
}
