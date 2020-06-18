//
// Created by agustin on 14/6/20.
//

#ifndef ARGENTUM_STATS_H
#define ARGENTUM_STATS_H

#include "../Config/Configuration.h"

//Clase que maneja el recibimiento de ataques, Player y Monster le delegan
//operaciones cuando deben modificar sus stats
class Stats {
private:
    unsigned int generalTimer;
    unsigned int meditationTimer;
    bool isMeditating;

    unsigned int constitution;
    unsigned int intelligence;
    unsigned int agility;
    unsigned int strength;

    unsigned int classLifeMultiplier;
    unsigned int raceLifeMultiplier;
    unsigned int classManaMultiplier;
    unsigned int raceManaMultiplier;

    unsigned int experience;
    unsigned int level;
    unsigned int currentMana;
    unsigned int currentLife;
    unsigned int maxMana;
    unsigned int maxLife;
public:
    Stats(Config::Race _race, Config::Class _class, unsigned int _level, unsigned int _experience);

    int getTotalDamage(int weaponDamage);

    unsigned int getLevel();

    void increaseExperience(unsigned int _experience);

    int modifyLife(int damage, unsigned int attackerLevel, unsigned int defense);
};


#endif //ARGENTUM_STATS_H
