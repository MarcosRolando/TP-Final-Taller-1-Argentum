//
// Created by ivan on 10/6/20.
//

#ifndef ARGENTUM_CALCULATOR_H
#define ARGENTUM_CALCULATOR_H

#include "Configuration.h"
#include <random>
#include <algorithm>


class Calculator {
public:

    static unsigned int calculateMaxLife(Config::Modifiers classMods, Config::Modifiers
    raceMods, unsigned int level);

    static unsigned int calculateMaxMana(Config::Modifiers classMods, Config::Modifiers
    raceMods, unsigned int level);

    static unsigned int calculateGoldDrop(unsigned int maxHealth);

    static unsigned int calculateMaxSafeGold(unsigned int level);

    static unsigned int calculateNextLevelXP(unsigned int level);

    static unsigned int calculateAttackXP(unsigned int dmg, unsigned int
    myLevel, unsigned int otherLevel);

    static unsigned int calculateKillXP(unsigned int dmg, unsigned int
    myLevel, unsigned int otherLevel, unsigned int otherMaxHealth);

    static int calculateDamage(unsigned int strength, int weaponDamage);

    static unsigned int calculateDefense(unsigned int minClothingDefense,
            unsigned int maxClothingDefense);

    static bool canDodge(Config::Modifiers classMods, Config::Modifiers raceMods);

    static int getRandomInt(int minRange, int maxRange);

private:
    static float _getRandomFloat(float minRange, float maxRange);
};


#endif //ARGENTUM_CALCULATOR_H
