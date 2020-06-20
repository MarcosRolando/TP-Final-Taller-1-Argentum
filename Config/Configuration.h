//
// Created by ivan on 8/6/20.
//

#ifndef ARGENTUM_CONFIGURATION_H
#define ARGENTUM_CONFIGURATION_H

#include "ConfigFileReader.h"
#include <unordered_map>

class Configuration {

private:
    std::unordered_map<Config::Race, Config::Modifiers> raceModifiers{};
    std::unordered_map<Config::Class, Config::Modifiers> classModifiers{};
    std::unordered_map<Config::Monster, Config::MonsterStats> monsterStats{};
    std::unordered_map<Config::Weapon, Config::WeaponData> weaponData{};
    std::unordered_map<Config::Clothing, Config::ClothingData> clothingData{};
    std::unordered_map<Config::Potion, Config::PotionData> potionData{};

    Config::GoldModifiers goldModifiers{};

    Config::XPModifiers xpModifiers{};

    float criticalAttackChance;
    float dodgeChance;

    unsigned int newbieLevel;
    unsigned int maxLevelDif;

    unsigned int playerVisionRange;

public:
    Configuration(Configuration const&) = delete;
    void operator=(Configuration const&) = delete;

    static Configuration& getInstance();

    Config::Modifiers configClassModifiers(Config::Class _class) const;

    Config::Modifiers configRaceModifiers(Config::Race race) const;

    Config::MonsterStats configMonsterStats(Config::Monster monster) const;

    Config::WeaponData configWeaponData(Config::Weapon weapon) const;

    Config::ClothingData configClothingData(Config::Clothing clothes) const;

    Config::PotionData configPotionData(Config::Potion potion) const;

    Config::GoldModifiers configGoldModifiers() const;
    Config::XPModifiers configXPModifiers() const;

    float configCriticalAttackChance() const;
    float configDodgeChance() const;
    unsigned int configNewbieLevel() const;
    unsigned int configMaxLevelDif() const;
    unsigned int configPlayerVisionRange() const;

private:
    Configuration();
};


#endif //ARGENTUM_CONFIGURATION_H
