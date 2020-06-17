//
// Created by agustin on 14/6/20.
//

#include "Stats.h"
#include <ctime>

Stats::Stats(Race _race, Class _class, unsigned int _level, unsigned int _experience) {

    isMeditating = false;
    generalTimer = time(nullptr);
    meditationTimer = generalTimer;
}
