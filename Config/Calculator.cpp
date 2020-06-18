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

/*unsigned int
Calculator::calculateDamage(Modifiers classMods, Modifiers raceMods,
                            WeaponStats weapon) {
    unsigned int totalStrength = classMods.strength + raceMods.strength;
    unsigned int minRange = weapon.minDmg;
    unsigned int maxRange = weapon.maxDmg;
    float random = _getRandomFloat(minRange, maxRange);
    return totalStrength * random;
}*/

unsigned int Calculator::calculateDamage(Modifiers classMods, Modifiers
raceMods, unsigned int minWeaponDmg, unsigned int maxWeaponDmg) {
    unsigned int totalStrength = classMods.strength + raceMods.strength;
    unsigned int random = _getRandomUInt(minWeaponDmg, maxWeaponDmg);
    return totalStrength * random;
}

/*unsigned int Calculator::calculateDefense(ClothingStats armor, ClothingStats
                                            shield, ClothingStats helmet) {
    unsigned int armorMinDef = armor.minDefense;
    unsigned int armorMaxDef = armor.maxDefense;

    unsigned int shieldMinDef = shield.minDefense;
    unsigned int shieldMaxDef = shield.maxDefense;

    unsigned int helmetMinDef = helmet.minDefense;
    unsigned int helmetMaxDef = helmet.maxDefense;

    float armorDef = _getRandomNumber(armorMinDef, armorMaxDef);
    float helmetDef = _getRandomNumber(helmetMinDef, helmetMaxDef);
    float shieldDef = _getRandomFloat(shieldMinDef, shieldMaxDef);

    return (armorDef + helmetDef + shieldDef);
}*/

unsigned int Calculator::calculateDefense(unsigned int minClothingDefense,
        unsigned int maxClothingDefense) {
    unsigned int clothingDef = _getRandomUInt(minClothingDefense,
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

unsigned int Calculator::_getRandomUInt(unsigned int minRange, unsigned int
maxRange) {
    std::random_device seed;
    std::default_random_engine generator(seed());
    std::uniform_int_distribution<int> dist(minRange, maxRange);
    return dist(generator);
}
