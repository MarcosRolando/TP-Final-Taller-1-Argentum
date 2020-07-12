#ifndef ARGENTUM_SOUNDREPOSITORY_H
#define ARGENTUM_SOUNDREPOSITORY_H


#include <iostream>
#include <unordered_map>
#include <queue>
#include "../../TPException.h"
#include "Sound.h"

//Despues prob dejems un solo Step/Attack/Explosion
enum SoundID {SwordAttack, Arrow, Explotion1, Explotion2, Explotion3,
        Punch, Death, Death2, Death3, Attack, Attack2, HeavyAttack, Step, Step1, Step2};

class SoundRepository {
private:
    std::unordered_map<SoundID, Sound> sounds;
    Mix_Music* music{};
public:
    /* Constructor */
    SoundRepository();

    Mix_Music* getMusic();

    Mix_Chunk* getSound(SoundID id);

    /* Destructor */
    ~SoundRepository();

private:
    void _loadSounds();
    void _loadMusic();
};


#endif //ARGENTUM_SOUNDREPOSITORY_H
