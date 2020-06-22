//
// Created by ivan on 8/6/20.
//

#ifndef ARGENTUM_CONFIGURATION_H
#define ARGENTUM_CONFIGURATION_H

#include "ConfigFileReader.h"
#include <unordered_map>

class Configuration {

private:
    std::unordered_map<GameType::Race, Config::Modifiers> raceModifiers{};
    std::unordered_map<GameType::Class, Config::Modifiers> classModifiers{};
    std::unordered_map<GameType::Monster, Config::MonsterStats> monsterStats{};
    std::unordered_map<GameType::Weapon, Config::WeaponData> weaponData{};
    std::unordered_map<GameType::Clothing, Config::ClothingData> clothingData{};
    std::unordered_map<GameType::Potion, Config::PotionData> potionData{};

    Config::GoldModifiers goldModifiers{};

    Config::XPModifiers xpModifiers{};

    float criticalAttackChance;
    float dodgeChance;

    unsigned int newbieLevel;
    unsigned int maxLevelDif;

    unsigned int timeBetweenMonsterSpawns{};
    unsigned int monsterSpawnAmount{};
    unsigned int maxMonsterAmount{};

    unsigned int initialMerchantGold;

    unsigned int playerVisionRange;

public:
    Configuration(Configuration const&) = delete;
    void operator=(Configuration const&) = delete;

    static Configuration& getInstance();

    Config::Modifiers configClassModifiers(GameType::Class _class) const;

    Config::Modifiers configRaceModifiers(GameType::Race race) const;

    Config::MonsterStats configMonsterStats(GameType::Monster monster) const;

    Config::WeaponData configWeaponData(GameType::Weapon weapon) const;

    Config::ClothingData configClothingData(GameType::Clothing clothes) const;

    Config::PotionData configPotionData(GameType::Potion potion) const;

    Config::GoldModifiers configGoldModifiers() const;

    Config::XPModifiers configXPModifiers() const;

    float configCriticalAttackChance() const;
    float configDodgeChance() const;
    unsigned int configNewbieLevel() const;
    unsigned int configMaxLevelDif() const;
    unsigned int configPlayerVisionRange() const;
    unsigned int configTimeBetweenMonsterSpawns() const;
    unsigned int configMaxMonsterAmount() const;
    unsigned int configMonsterSpawnAmount() const;
    unsigned int configInitialMerchantGold() const;

private:
    Configuration();
};


#endif //ARGENTUM_CONFIGURATION_H