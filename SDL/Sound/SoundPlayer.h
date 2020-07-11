//
// Created by ivan on 22/6/20.
//

#ifndef ARGENTUM_SOUNDPLAYER_H
#define ARGENTUM_SOUNDPLAYER_H

#include "SoundRepository.h"
#include <mutex>

class SoundPlayer {
private:
    std::queue<SoundID> soundQueue;
    SoundRepository repo;
    std::mutex m;
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


    static bool isMusicPlaying();
};


#endif //ARGENTUM_SOUNDPLAYER_H
