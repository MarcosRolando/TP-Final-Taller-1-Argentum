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
    float exponent = Configuration::getInstance()
            .configGoldModifiers().safeGoldLevelModifier;
    return (multiplier * pow(level, exponent));
}

unsigned int Calculator::calculateNextLevelXP(unsigned int level) {
    unsigned int multiplier = Configuration::getInstance().configXPModifiers
            ().nextLevelFactor;
    float exponent = Configuration::getInstance().configXPModifiers
            ().nextLevelModifier;

    return (multiplier * pow(level, exponent));
}

unsigned int Calculator::calculateAttackXP(unsigned int dmg, unsigned int
myLevel, unsigned int otherLevel) {
    unsigned int modifier = Configuration::getInstance().configXPModifiers()
            .attackXPModifier;

    int multiplier = otherLevel - myLevel + modifier;
    return dmg * std::max(multiplier, 0);
}

unsigned int Calculator::calculateKillXP(unsigned int dmg, unsigned int myLevel,
                                         unsigned int otherLevel,
                                         unsigned int otherMaxHealth) {
    unsigned int modifier = Configuration::getInstance().configXPModifiers()
            .killXPModifier;
    int multiplier = otherLevel - myLevel + modifier;
    float minRange = Configuration::getInstance().configXPModifiers()
            .killXPMinRange;
    float maxRange = Configuration::getInstance().configXPModifiers()
            .killXPMaxRange;
    float random = _getRandomNumber(minRange, maxRange);

    return (random * otherMaxHealth * std::max(multiplier, 0));
}

unsigned int
Calculator::calculateDamage(Modifiers classMods, Modifiers raceMods,
                            WeaponStats weapon) {
    unsigned int totalStrength = classMods.strength + raceMods.strength;
    unsigned int minRange = weapon.minDmg;
    unsigned int maxRange = weapon.maxDmg;
    float random = _getRandomNumber(minRange, maxRange);
    return totalStrength * random;
}

unsigned int Calculator::calculateDefense(ClothingStats armor, ClothingStats
shield, ClothingStats helmet) {
    unsigned int armorMinDef = armor.minDefense;
    unsigned int armorMaxDef = armor.maxDefense;

    unsigned int shieldMinDef = shield.minDefense;
    unsigned int shieldMaxDef = shield.maxDefense;

    unsigned int helmetMinDef = helmet.minDefense;
    unsigned int helmetMaxDef = helmet.maxDefense;

    float armorDef = _getRandomNumber(armorMinDef, armorMaxDef);
    float helmetDef = _getRandomNumber(helmetMinDef, helmetMaxDef);
    float shieldDef = _getRandomNumber(shieldMinDef, shieldMaxDef);

    return (armorDef + helmetDef + shieldDef);
}

bool Calculator::canDodge(Modifiers classMods, Modifiers raceMods) {
    float random = _getRandomNumber(0, 1);
    unsigned int totalAgility = classMods.agility + raceMods.agility;

    return (pow(random, totalAgility) < 0.001);
}

float Calculator::_getRandomNumber(float minRange, float maxRange) {
    std::random_device seed;
    std::default_random_engine generator(seed());
    std::uniform_real_distribution<float> dist(minRange, maxRange);
    return dist(generator);
}
