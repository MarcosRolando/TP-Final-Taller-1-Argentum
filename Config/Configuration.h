//
// Created by ivan on 8/6/20.
//

#ifndef ARGENTUM_CONFIGURATION_H
#define ARGENTUM_CONFIGURATION_H

#include "ConfigFileReader.h"

class Configuration {

private:
    std::unordered_map<Race, Modifiers> raceModifiers;
    std::unordered_map<Class, Modifiers> classModifiers;
    std::unordered_map<Monster, MonsterStats> monsterStats;

    std::unordered_map<Weapon, WeaponStats> weaponStats;
    std::unordered_map<Clothing, ClothingStats> clothingStats;

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
