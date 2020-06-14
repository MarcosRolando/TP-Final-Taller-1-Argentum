//
// Created by agustin on 14/6/20.
//

#include "Stats.h"

#include <time.h>

Stats::Stats(unsigned int _constitution, unsigned int _intelligence,
             unsigned int _agility, unsigned int _classLifeMultiplier,
             unsigned int _raceLifeMultiplier, unsigned int _classManaMultiplier,
             unsigned int _raceManaMultiplier, unsigned int _experience,
             unsigned int _level) {
    constitution = _constitution;
    intelligence = _intelligence;
    agility = _agility;
    classLifeMultiplier = _classLifeMultiplier;
    raceLifeMultiplier = _raceLifeMultiplier;
    raceManaMultiplier = _raceManaMultiplier;
    classManaMultiplier = _classManaMultiplier;
    experience = _experience;
    level = _level;
    isMeditating = false;
    generalTimer = time(0);
    meditationTimer = generalTimer;
}
