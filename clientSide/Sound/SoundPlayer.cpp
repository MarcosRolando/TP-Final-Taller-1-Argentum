//
// Created by ivan on 22/6/20.
//

#include "SoundPlayer.h"

#define QUEUE_SIZE 3

const int TIME_BETWEEN_SOUND_UPDATES = 250;

SoundPlayer::SoundPlayer() {
    std::srand(std::clock());
    timer.start();
}

void SoundPlayer::playMusic() {
    std::lock_guard<std::mutex> l(m);
    if( Mix_PlayingMusic() == 0 ) {//Empieza musica si no habia
        Mix_PlayMusic(repo.getMusic(), -1);
    } else if (Mix_PausedMusic() == 1) {//Resume musica si estaba en pausa
        Mix_ResumeMusic();
    }
}

void SoundPlayer::pauseMusic() {
    std::lock_guard<std::mutex> l(m);
    Mix_PauseMusic();
}

bool SoundPlayer::isMusicPlaying(){
    return !Mix_PausedMusic();
}

SoundID SoundPlayer::_getRandomDeathSound() {
    int rand = std::rand() % 2;
    switch (rand) {
        case 0:
            return Death1Sound;
        case 1:
            return Death2Sound;
        default:
            return Death1Sound;
    }
}

void SoundPlayer::queueSound(SoundID id) {
    std::lock_guard<std::mutex> l(m);
    if (timer.getTime() > TIME_BETWEEN_SOUND_UPDATES) {
        blocked = false;
    }
    if (!blocked) {
        if (id == Death1Sound) id = _getRandomDeathSound();
        if (soundQueue.size() < QUEUE_SIZE)
            soundQueue.push(id);
    }
}

void SoundPlayer::playSounds() {
    std::lock_guard<std::mutex> l(m);
    Mix_Chunk* soundToPlay;
    long unsigned int queueSize = soundQueue.size();
    for (long unsigned int i = 0; i < queueSize; i++){
        soundToPlay = repo.getSound(soundQueue.front());
        Mix_PlayChannel(-1, soundToPlay, 0);
        soundQueue.pop();
    }
    if (!blocked) {
        blocked = true;
        timer.start();
    }
}
