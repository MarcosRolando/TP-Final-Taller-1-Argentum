#ifndef ARGENTUM_SOUNDREPOSITORY_H
#define ARGENTUM_SOUNDREPOSITORY_H


#include <iostream>
#include <unordered_map>
#include <queue>

#include "../SDLException.h"
#include "Sound.h"

enum SoundID {Attack, Explotion, Punch, StepDirt};

class SoundRepository {
private:
    std::unordered_map<SoundID, Sound> sounds;
    std::queue<SoundID> soundQueue;
    Mix_Music* music;
public:
    /* Constructor */
    SoundRepository();
    /* Encola un sonido */
    void queueSound(SoundID id);
    /* Reproduce los sonidos que estan encolados */
    void playSounds();
    /* Reproduce la musica */
    void playMusic();
    /* Pausa la musica */
    void pauseMusic();
    /* Destructor */
    ~SoundRepository();

private:
    void _init();
    void _loadSounds();
    void _loadMusic();
};


#endif //ARGENTUM_SOUNDREPOSITORY_H
