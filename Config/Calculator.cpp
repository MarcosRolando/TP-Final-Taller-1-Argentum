//
// Created by ivan on 10/6/20.
//

#include "Calculator.h"

using namespace Config;

unsigned int Calculator::calculateMaxLife(Modifiers classMods, Modifiers
                                            raceMods, unsigned int level) {
    unsigned int totalConstitution = classMods.constitution + raceMods
            .constitution;

    return totalConstitution * classMods.lifeMultiplier * raceMods.lifeMultiplier * level;
}

unsigned int Calculator::calculateMaxMana(Modifiers classMods, Modifiers
                                            raceMods, unsigned int level) {
    unsigned int totalIntelligence = classMods.intelligence + raceMods
            .intelligence;

    return totalIntelligence * classMods.manaMultiplier * raceMods.manaMultiplier * level;
}

unsigned int Calculator::calculateGoldDrop(unsigned int maxHealth) {

    float minRange = Configuration::getInstance().configGoldModifiers()
            .goldDropFactorMin;
    float maxRange = Configuration::getInstance().configGoldModifiers()
            .goldDropFactorMax;
    float randNum = _getRandomFloat(minRange, maxRange);

    return (static_cast<unsigned int>(randNum) * maxHealth);
}

unsigned int Calculator::calculateMaxSafeGold(unsigned int level) {
    unsigned int multiplier = Configuration::getInstance()
            .configGoldModifiers().safeGoldFactor;
    float exponent = Configuration::getInstance()
            .configGoldModifiers().safeGoldLevelModifier;
    return (multiplier * static_cast<unsigned int>(pow(level, exponent)));
}

unsigned int Calculator::calculateNextLevelXP(unsigned int level) {
    unsigned int multiplier = Configuration::getInstance().configXPModifiers
            ().nextLevelFactor;
    float exponent = Configuration::getInstance().configXPModifiers
            ().nextLevelModifier;

    return (multiplier * static_cast<unsigned int>(pow(level, exponent)));
}

unsigned int Calculator::calculateAttackXP(unsigned int dmg, unsigned int
                                    myLevel, unsigned int otherLevel) {
    unsigned int modifier = Configuration::getInstance().configXPModifiers()
            .attackXPModifier;

    int multiplier = static_cast<int>(otherLevel - myLevel + modifier);
    return dmg * std::max(multiplier, 0);
}

unsigned int Calculator::calculateKillXP(unsigned int dmg, unsigned int myLevel,
                                         unsigned int otherLevel,
                                         unsigned int otherMaxHealth) {
    unsigned int modifier = Configuration::getInstance().configXPModifiers()
            .killXPModifier;
    int multiplier = static_cast<int>((otherLevel - myLevel + modifier));
    float minRange = Configuration::getInstance().configXPModifiers()
            .killXPMinRange;
    float maxRange = Configuration::getInstance().configXPModifiers()
            .killXPMaxRange;
    float random = _getRandomFloat(minRange, maxRange);

    return static_cast<unsigned int>((random * static_cast<float>(otherMaxHealth) * std::max(multiplier, 0)));
}


int Calculator::calculateDamage(unsigned int strength, int weaponDamage) {
    return strength * weaponDamage;
}

unsigned int Calculator::calculateDefense(unsigned int minClothingDefense,
        unsigned int maxClothingDefense) {
    unsigned int clothingDef = getRandomInt(minClothingDefense,
                                        maxClothingDefense);

    return clothingDef;
}

bool Calculator::canDodge(Modifiers classMods, Modifiers raceMods) {
    float random = _getRandomFloat(0, 1);
    unsigned int totalAgility = classMods.agility + raceMods.agility;

    return (pow(random, totalAgility) < 0.001);
}

float Calculator::_getRandomFloat(float minRange, float maxRange) {
    std::random_device seed;
    std::default_random_engine generator(seed());
    std::uniform_real_distribution<float> dist(minRange, maxRange);
    return dist(generator);
}

int Calculator::getRandomInt(int minRange, int maxRange) {
    std::random_device seed;
    std::default_random_engine generator(seed());
    std::uniform_int_distribution<int> dist(minRange, maxRange);
    return dist(generator);
}
