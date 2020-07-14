#ifndef ARGENTUM_SOUNDREPOSITORY_H
#define ARGENTUM_SOUNDREPOSITORY_H


#include <iostream>
#include <unordered_map>
#include <queue>
#include "../../libs/TPException.h"
#include "Sound.h"

//Despues prob dejems un solo Step/Attack/Explosion
enum SoundID {SwordAttackSound, ArrowSound, Explotion1Sound, Explotion2Sound, Explotion3Sound,
        Death1Sound, Death2Sound, Attack1Sound, Attack2Sound, HeavyAttackSound, StepSound, HealingSound,
        ZombieSound, SpiderSound};

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
