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

    Modifiers configClassModifiers(Class _class) const;

    Modifiers configRaceModifiers(Race race) const;

    MonsterStats configMonsterStats(Monster monster) const;

    WeaponStats configWeaponStats(Weapon weapon) const;

    ClothingStats configClothingStats(Clothing clothes) const;

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
