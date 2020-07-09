//
// Created by ivan on 10/6/20.
//

#include "Calculator.h"
#include "Configuration.h"
#include <random>

const float CRITICAL_PROBABILITY = 0.05;

using namespace Config;

bool Calculator::isCritical() {
    std::random_device seed;
    std::default_random_engine generator(seed());
    std::bernoulli_distribution dist(CRITICAL_PROBABILITY);
    return dist(generator);
}

int Calculator::calculateMaxLife(unsigned int constitution, unsigned int classLifeMultiplier,
                                unsigned int raceLifeMultiplier, unsigned int level) {
    return static_cast<int>(constitution * classLifeMultiplier * raceLifeMultiplier * level);
}

unsigned int Calculator::calculateMaxMana(unsigned int intelligence, unsigned int classManaMultiplier,
                                            unsigned int raceManaMultiplier, unsigned int level) {
    return intelligence * classManaMultiplier * raceManaMultiplier * level;
}

unsigned int Calculator::calculateGoldDrop(unsigned int maxLife) {

    float minRange = Configuration::getInstance().configGoldModifiers()
            .goldDropFactorMin;
    float maxRange = Configuration::getInstance().configGoldModifiers()
            .goldDropFactorMax;
    float randNum = _getRandomFloat(minRange, maxRange);

    return static_cast<unsigned int>(randNum * maxLife);
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
    return (dmg * std::max(multiplier, 0));
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

int Calculator::lifeRecovered(unsigned int recoveryRate, double timeElpased) {
    return static_cast<int>(static_cast<double>(recoveryRate) * timeElpased);
}

unsigned int Calculator::manaRecoveredNoMeditation(unsigned int recoveryRate, double timeElpased) {
    return static_cast<int>(static_cast<double>(recoveryRate) * timeElpased);
}

unsigned int Calculator::manaRecoveredWithMeditation(unsigned int meditationRate,
                                        unsigned int intelligence, double timeElpased) {

    return static_cast<int>(static_cast<double>(meditationRate * intelligence) * timeElpased);
}
