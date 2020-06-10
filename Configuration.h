//
// Created by ivan on 8/6/20.
//

#ifndef ARGENTUM_CONFIGURATION_H
#define ARGENTUM_CONFIGURATION_H

#include "FileReader.h"
#include <iostream>
#include <vector>

struct Modifiers {
    unsigned int health;
    unsigned int mana;
    unsigned int constitution;
    unsigned int intelligence;
    unsigned int agility;
    unsigned int strength;
    unsigned int meditationRate;
};

struct WeaponStats {
    unsigned int minDmg;
    unsigned int maxDmg;
    unsigned int manaConsumption;
    unsigned int range;
};

struct ArmorStats {
    unsigned int minDefense;
    unsigned int maxDefense;
};

struct MonsterStats {
    int health;
    unsigned int damage;
    unsigned int rangeOfVision;
    unsigned int minLevel;
    unsigned int maxLevel;
};


struct GoldModifiers {
    float goldDropFactorMin;
    float goldDropFactorMax;
    unsigned int safeGoldFactor;
    float safeGoldLevelModifier;
};

struct XPModifiers {
    unsigned int nextLevelFactor;
    float nextLevelModifier;
    unsigned int attackXPModifier;
    float killXPMinModifier;
    float killXPMaxModifier;
};

class Configuration {

private:
    std::vector<Modifiers> raceModifiers;
    std::vector<Modifiers> classModifiers;
    std::vector<MonsterStats> monsterStats;

    GoldModifiers goldModifiers;

    XPModifiers xpModifiers;

    float criticalAttackChance;
    float dodgeChance;

    unsigned int newbieLevel;
    unsigned int maxLevelDif;

    unsigned int playerVisionRange;

public:
    Configuration(Configuration const&) = delete;
    void operator=(Configuration const&) = delete;

    static Configuration& getInstance();

    Modifiers configMageModifiers();
    Modifiers configClericModifiers();
    Modifiers configPaladinModifiers();
    Modifiers configWarriorModifiers();

    Modifiers configHumanModifiers();
    Modifiers configElfModifiers();
    Modifiers configDwarfModifiers();
    Modifiers configGnomeModifiers();

    MonsterStats configSkeletonStats();
    MonsterStats configSpiderStats();
    MonsterStats configZombieStats();
    MonsterStats configGoblinStats();

    GoldModifiers configGoldModifiers();
    XPModifiers configXPModifiers();

    float configCriticalAttackChance() const;
    float configDodgeChance() const;
    unsigned int configNewbieLevel() const;
    unsigned int configMaxLevelDif() const;
    unsigned int configPlayerVisionRange() const;

private:
    Configuration();
};


#endif //ARGENTUM_CONFIGURATION_H
