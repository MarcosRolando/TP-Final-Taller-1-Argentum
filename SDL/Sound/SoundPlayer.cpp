//
// Created by ivan on 22/6/20.
//

#include "SoundPlayer.h"

#define QUEUE_SIZE 3

SoundPlayer::SoundPlayer(){
    srand(clock());
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
    int rand = std::rand() % 3;
    switch (rand) {
        case 0:
            return Death;
        case 1:
            return Death2;
        case 2:
            return Death3;
        default:
            return Death2;
    }
}

void SoundPlayer::queueSound(SoundID id) {
    std::lock_guard<std::mutex> l(m);
    if (id == Death) id = _getRandomDeathSound();
    if (soundQueue.size() < QUEUE_SIZE)
        soundQueue.push(id);
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
}

SoundPlayer::~SoundPlayer() {

}
