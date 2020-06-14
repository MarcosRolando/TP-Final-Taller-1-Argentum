//
// Created by agustin on 14/6/20.
//

#ifndef ARGENTUM_STATS_H
#define ARGENTUM_STATS_H

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

    unsigned int classLifeMultiplier;
    unsigned int raceLifeMultiplier;
    unsigned int classManaMultiplier;
    unsigned int raceManaMultiplier;

    unsigned int experience;
    unsigned int level;
    unsigned int currentMana;
    unsigned int currentLife;
public:
    Stats(unsigned int constitution, unsigned int intelligence, unsigned int agility,
          unsigned int classLifeMultiplier, unsigned int raceLifeMultiplier,
          unsigned int classManaMultiplier, unsigned int raceManaMultiplier,
          unsigned int experience, unsigned int level);

};


#endif //ARGENTUM_STATS_H
