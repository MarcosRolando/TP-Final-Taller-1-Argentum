//
// Created by ivan on 8/6/20.
//

#include "Configuration.h"

using namespace Config;

Configuration& Configuration::getInstance() {
    static Configuration instance;
    return instance;
}

Configuration::Configuration() {
    ConfigFileReader fileReader("../config.json");

    fileReader.loadClassModifiers(classModifiers);
    fileReader.loadRaceModifiers(raceModifiers);
    fileReader.loadMonsterStats(monsterStats);

    fileReader.loadWeaponData(WeaponData);
    fileReader.loadClothingData(ClothingData);

    fileReader.loadGoldModifiers(goldModifiers);
    fileReader.loadXPModifiers(xpModifiers);

    criticalAttackChance = fileReader.loadCritAttackChance();
    dodgeChance = fileReader.loadDodgeChance();

    newbieLevel = fileReader.loadNewbieLevel();
    maxLevelDif = fileReader.loadmaxLevelDif();
    playerVisionRange = fileReader.loadPlayerVisionRange();
}

Modifiers Configuration::configClassModifiers(Class _class) const{
    return classModifiers.at(_class);
}

Modifiers Configuration::configRaceModifiers(Race race) const{
    return raceModifiers.at(race);
}

MonsterStats Configuration::configMonsterStats(Monster monster) const{
    return monsterStats.at(monster);
}

WeaponData Configuration::configWeaponData(Weapon weapon) const{
    return WeaponData.at(weapon);
}

ClothingData Configuration::configClothingData(Clothing clothes) const{
    return ClothingData.at(clothes);
}

GoldModifiers Configuration::configGoldModifiers() const{
    return goldModifiers;
}

XPModifiers Configuration::configXPModifiers() const{
    return xpModifiers;
}

float Configuration::configCriticalAttackChance() const{
    return criticalAttackChance;
}

float Configuration::configDodgeChance() const{
    return dodgeChance;
}

unsigned int Configuration::configNewbieLevel() const{
    return newbieLevel;
}

unsigned int Configuration::configMaxLevelDif() const{
    return maxLevelDif;
}

unsigned int Configuration::configPlayerVisionRange() const {
    return playerVisionRange;
}
