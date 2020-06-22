//
// Created by ivan on 22/6/20.
//

#include "SoundPlayer.h"

#define QUEUE_SIZE 3

SoundPlayer::SoundPlayer(SoundRepository& repo) : repo(repo){}

void SoundPlayer::playMusic() {
    if( Mix_PlayingMusic() == 0 ) {//Empieza musica si no habia
        Mix_PlayMusic(repo.getMusic(), -1);
    } else if (Mix_PausedMusic() == 1) {//Resume musica si estaba en pausa
        Mix_ResumeMusic();
    }
}

void SoundPlayer::pauseMusic() {
    Mix_PauseMusic();
}

bool SoundPlayer::isMusicPlaying(){
    return Mix_PausedMusic();
}


void SoundPlayer::queueSound(SoundID id) {
    if (soundQueue.size() < QUEUE_SIZE)
        soundQueue.push(id);
}

void SoundPlayer::playSounds() {
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
