//
// Created by ivan on 22/6/20.
//

#ifndef ARGENTUM_SOUNDPLAYER_H
#define ARGENTUM_SOUNDPLAYER_H

#include "SoundRepository.h"
#include <mutex>
#include "../../libs/Timer.h"

class SoundPlayer {
private:
    std::queue<SoundID> soundQueue;
    SoundRepository repo;
    std::mutex m;
    Timer timer;
    bool blocked{false}; /*Para regular que no le puedan meter muchos sonidos en poco tiempo*/

public:
    SoundPlayer();
    /* Encola un sonido */
    void queueSound(SoundID id);
    /* Reproduce los sonidos que estan encolados */
    void playSounds();
    /* Reproduce la musica */
    void playMusic();
    /* Pausa la musica */
    void pauseMusic();
    /* Devuelve true si la musica se esta reproduciendo */
    static bool isMusicPlaying();
private:
    static SoundID _getRandomDeathSound();
};


#endif //ARGENTUM_SOUNDPLAYER_H
