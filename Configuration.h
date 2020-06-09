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
    Modifiers humanModifiers;
    Modifiers elfModifiers;
    Modifiers dwarfModifiers;
    Modifiers gnomeModifiers;

    Modifiers mageModifiers;
    Modifiers clericModifiers;
    Modifiers paladinModifiers;
    Modifiers warriorModifiers;

    MonsterStats zombieStats;
    MonsterStats skeletonStats;
    MonsterStats goblinStats;
    MonsterStats spiderStats;

    GoldModifiers goldModifiers;

    XPModifiers xpModifiers;

    float criticalAttackChance;
    float dodgeChance;

    unsigned int newbieLevel;
    unsigned int maxLevelDif;

    unsigned int inventorySize;
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

    float configCriticalAttackChance();
    float configDodgeChance();
    unsigned int configNewbieLevel();
    unsigned int configMaxLevelDif();
    unsigned int configInventorySize();
    unsigned int configPlayerVisionRange();

private:
    Configuration();
};


#endif //ARGENTUM_CONFIGURATION_H
