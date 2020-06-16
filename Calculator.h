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

    static unsigned int calculateMaxHealth(Modifiers classMods, Modifiers
    raceMods, unsigned int level);

    static unsigned int calculateMaxMana(Modifiers classMods, Modifiers
    raceMods, unsigned int level);

    static unsigned int calculateGoldDrop(unsigned int maxHealth);

    static unsigned int calculateMaxSafeGold(unsigned int level);

    static unsigned int calculateNextLevelXP(unsigned int level);

    static unsigned int calculateAttackXP(unsigned int dmg, unsigned int
    myLevel, unsigned int otherLevel);

    static unsigned int calculateKillXP(unsigned int dmg, unsigned int
    myLevel, unsigned int otherLevel, unsigned int otherMaxHealth);

    //static unsigned int calculateDamage(Modifiers classMods, Modifiers
    //raceMods, WeaponStats weapon);

    static unsigned int calculateDamage(Modifiers classMods, Modifiers
    raceMods, unsigned int minWeaponDmg, unsigned int maxWeaponDmg);

    //static unsigned int calculateDefense(ClothingStats armor, ClothingStats
    //shield, ClothingStats helmet);

    static unsigned int calculateDefense(unsigned int minClothingDefense,
            unsigned int maxClothingDefense);

    static bool canDodge(Modifiers classMods, Modifiers raceMods);

private:
    static float _getRandomFloat(float minRange, float maxRange);
    static unsigned int _getRandomUInt(unsigned int minRange, unsigned int
    maxRange);
};


#endif //ARGENTUM_CALCULATOR_H
