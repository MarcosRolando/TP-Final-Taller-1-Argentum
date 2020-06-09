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

public:
    Configuration(Configuration const&) = delete;
    void operator=(Configuration const&) = delete;

    static Configuration& getInstance();

    Modifiers getMageModifiers();
    Modifiers getClericModifiers();
    Modifiers getPaladinModifiers();
    Modifiers getWarriorModifiers();

    Modifiers getHumanModifiers();
    Modifiers getElfModifiers();
    Modifiers getDwarfModifiers();
    Modifiers getGnomeModifiers();

    MonsterStats getSkeletonStats();
    MonsterStats getSpiderStats();
    MonsterStats getZombieStats();
    MonsterStats getGoblinStats();

    GoldModifiers getGoldModifiers();
    XPModifiers getXPModifiers();

    float getCriticalAttackChance();
    float getDodgeChance();
    unsigned int getNewbieLevel();
    unsigned int getMaxLevelDif();

private:
    Configuration();


};


#endif //ARGENTUM_CONFIGURATION_H
