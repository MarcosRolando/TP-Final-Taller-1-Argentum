//
// Created by ivan on 10/6/20.
//

#include "Calculator.h"

using namespace Config;

int Calculator::calculateMaxLife(Modifiers classMods, Modifiers
                                            raceMods, unsigned int level) {
    unsigned int totalConstitution = classMods.constitution + raceMods
            .constitution;

    return static_cast<int>(totalConstitution * classMods.lifeMultiplier * raceMods.lifeMultiplier * level);
}

unsigned int Calculator::calculateMaxMana(Modifiers classMods, Modifiers
                                            raceMods, unsigned int level) {
    unsigned int totalIntelligence = classMods.intelligence + raceMods
            .intelligence;

    return totalIntelligence * classMods.manaMultiplier * raceMods.manaMultiplier * level;
}

unsigned int Calculator::calculateGoldDrop(unsigned int maxLife) {

    float minRange = Configuration::getInstance().configGoldModifiers()
            .goldDropFactorMin;
    float maxRange = Configuration::getInstance().configGoldModifiers()
            .goldDropFactorMax;
    float randNum = _getRandomFloat(minRange, maxRange);

    return (static_cast<unsigned int>(randNum) * maxLife);
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

unsigned int Calculator::calculateKillXP(unsigned int myLevel,
                                         unsigned int otherLevel,
                                         unsigned int othermaxLife) {
    unsigned int modifier = Configuration::getInstance().configXPModifiers()
            .killXPModifier;
    int multiplier = static_cast<int>((otherLevel - myLevel + modifier));
    float minRange = Configuration::getInstance().configXPModifiers()
            .killXPMinRange;
    float maxRange = Configuration::getInstance().configXPModifiers()
            .killXPMaxRange;
    float random = _getRandomFloat(minRange, maxRange);

    return static_cast<unsigned int>((random * static_cast<float>(othermaxLife) * std::max(multiplier, 0)));
}


int Calculator::calculateDamage(unsigned int strength, int weaponDamage) {
    return static_cast<int>(strength) * weaponDamage;
}

bool Calculator::canDodge(unsigned int agility) {
    float random = _getRandomFloat(0, 1);
    return (pow(random, agility) < 0.001);
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
