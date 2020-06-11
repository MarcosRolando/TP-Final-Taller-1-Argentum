//
// Created by ivan on 10/6/20.
//

#include "Calculator.h"

unsigned int Calculator::calculateMaxHealth(Modifiers classMods, Modifiers
raceMods, unsigned int level) {
    unsigned int totalConstitution = classMods.constitution + raceMods
            .constitution;

    return totalConstitution * classMods.health * raceMods.health * level;
}

unsigned int Calculator::calculateMaxMana(Modifiers classMods, Modifiers
raceMods, unsigned int level) {
    unsigned int totalIntelligence = classMods.intelligence + raceMods
            .intelligence;

    return totalIntelligence * classMods.mana * raceMods.mana * level;
}

unsigned int Calculator::calculateGoldDrop(unsigned int maxHealth) {

    float minRange = Configuration::getInstance().configGoldModifiers()
            .goldDropFactorMin;
    float maxRange = Configuration::getInstance().configGoldModifiers()
            .goldDropFactorMax;
    float randNum = _getRandomNumber(minRange, maxRange);

    return (randNum * maxHealth);
}

unsigned int Calculator::calculateMaxSafeGold(unsigned int level) {
    unsigned int multiplier = Configuration::getInstance()
            .configGoldModifiers().safeGoldFactor;
    float exp = Configuration::getInstance()
            .configGoldModifiers().safeGoldLevelModifier;
    return (multiplier * pow(level, exp));
}

unsigned int Calculator::calculateNextLevelXP(unsigned int level) {
    return 0;
}

unsigned int
Calculator::calculateAttackXP(unsigned int dmg, unsigned int myLevel,
                              unsigned int otherLevel) {
    return 0;
}

unsigned int Calculator::calculateKillXP(unsigned int dmg, unsigned int myLevel,
                                         unsigned int otherLevel,
                                         unsigned int otherMaxHealth) {
    return 0;
}

unsigned int
Calculator::calculateDamage(Modifiers classMods, Modifiers raceMods,
                            WeaponStats weapon) {
    return 0;
}

unsigned int
Calculator::calculateDefense(ClothingStats armor, ClothingStats shield,
                             ClothingStats helmet) {
    return 0;
}

bool Calculator::canDodge(Modifiers classMods, Modifiers raceMods) {
    return false;
}

float Calculator::_getRandomNumber(float minRange, float maxRange) {
    std::random_device seed;
    std::default_random_engine generator(seed());
    std::uniform_real_distribution<float> dist(minRange, maxRange);
    return dist(generator);
}
