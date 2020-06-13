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
    unsigned int recoveryRate;
};

struct WeaponStats {
    unsigned int minDmg;
    unsigned int maxDmg;
    unsigned int manaConsumption;
    unsigned int range;
};

struct ClothingStats {
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
    unsigned int killXPModifier;
    float killXPMinRange;
    float killXPMaxRange;
};

class Configuration {

private:
    std::vector<Modifiers> raceModifiers;
    std::vector<Modifiers> classModifiers;
    std::vector<MonsterStats> monsterStats;

    std::vector<WeaponStats> weaponStats;
    std::vector<ClothingStats> clothingStats;

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

    Modifiers configMageModifiers() const;
    Modifiers configClericModifiers() const;
    Modifiers configPaladinModifiers() const;
    Modifiers configWarriorModifiers() const;

    Modifiers configHumanModifiers() const;
    Modifiers configElfModifiers() const;
    Modifiers configDwarfModifiers() const;
    Modifiers configGnomeModifiers() const;

    MonsterStats configSkeletonStats() const;
    MonsterStats configSpiderStats() const;
    MonsterStats configZombieStats() const;
    MonsterStats configGoblinStats() const;

    WeaponStats configLongSwordStats() const;
    WeaponStats configAxeStats() const;
    WeaponStats configWarhammerStats() const;
    WeaponStats configAshRodStats() const;
    WeaponStats configElvenFluteStats() const;
    WeaponStats configLinkedStaffStats() const;
    WeaponStats configSimpleBowStats() const;
    WeaponStats configCompoundBowStats() const;

    ClothingStats configCommonClothingStats() const;
    ClothingStats configLeatherArmorStats() const;
    ClothingStats configPlateArmorStats() const;
    ClothingStats configBlueTunicStats() const;
    ClothingStats configHoodStats() const;
    ClothingStats configIronHelmetStats() const;
    ClothingStats configTurtleShieldStats() const;
    ClothingStats configIronShieldStats() const;
    ClothingStats configMagicHatStats() const;

    GoldModifiers configGoldModifiers() const;
    XPModifiers configXPModifiers() const;

    float configCriticalAttackChance() const;
    float configDodgeChance() const;
    unsigned int configNewbieLevel() const;
    unsigned int configMaxLevelDif() const;
    unsigned int configPlayerVisionRange() const;

private:
    Configuration();


};


#endif //ARGENTUM_CONFIGURATION_H
