//
// Created by ivan on 22/6/20.
//

#ifndef ARGENTUM_SOUNDPLAYER_H
#define ARGENTUM_SOUNDPLAYER_H

#include "SoundRepository.h"

class SoundPlayer {
private:
    std::queue<SoundID> soundQueue;
    SoundRepository repo;
public:
    SoundPlayer();

    void queueSound(SoundID id);
    /* Reproduce los sonidos que estan encolados */
    void playSounds();
    /* Reproduce la musica */
    void playMusic();
    /* Pausa la musica */
    void pauseMusic();

    ~SoundPlayer();


    bool isMusicPlaying();
};


#endif //ARGENTUM_SOUNDPLAYER_H
