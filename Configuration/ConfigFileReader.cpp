//
// Created by ivan on 8/6/20.
//

#include "ConfigFileReader.h"
#include "../SDL/TPException.h"

ConfigFileReader::ConfigFileReader(const std::string& path) {
    file.open(path);
    try {
        reader.parse(file, obj);
    } catch (...) {
        file.close();
        throw TPException("Fallo el parseo del Config!");
    }
}

ConfigFileReader::~ConfigFileReader() {
    file.close();
}

void ConfigFileReader::loadClassModifiers(std::vector<Modifiers> &mods) {
    Json::Value& classModifiers = obj["Class"];
    Modifiers currMods{};
    for (auto & classModifier : classModifiers) {
       _getModifiers(currMods, classModifier);
       mods.push_back(currMods);
    }
}

void ConfigFileReader::loadRaceModifiers(std::vector<Modifiers> &mods) {
    Json::Value& raceModifiers = obj["Race"];
    Modifiers currMods{};
    for (auto & raceModifier : raceModifiers) {
        _getModifiers(currMods, raceModifier);
        mods.push_back(currMods);
    }
}

void ConfigFileReader::loadWeaponStats(std::vector<WeaponStats>& stats) {
    Json::Value& weapons = obj["Weapon"];
    WeaponStats currStats{};
    for (auto & weapon : weapons) {
        _getWeaponStats(currStats, weapon);
        stats.push_back(currStats);
    }
}

void ConfigFileReader::loadClothingStats(std::vector<ClothingStats>& stats) {
    Json::Value& clothings = obj["Clothing"];
    ClothingStats currStats{};
    for (auto & clothing : clothings) {
        _getClothingStats(currStats, clothing);
        stats.push_back(currStats);
    }
}


void ConfigFileReader::loadMonsterStats(std::vector<MonsterStats>& stats) {
    Json::Value& monsterStats = obj["Monster"];
    MonsterStats currStats{};
    for (auto & monsterStat : monsterStats) {
        _getMonsterStats(currStats, monsterStat);
        stats.push_back(currStats);
    }
}

void ConfigFileReader::loadGoldModifiers(GoldModifiers &goldModifiers) {
    Json::Value& modifiers = obj["GoldModifiers"];
    goldModifiers.safeGoldFactor = modifiers["MaxSafeGoldFactor"].asUInt();
    goldModifiers.safeGoldLevelModifier = modifiers["MaxGoldLevelModifier"]
            .asFloat();
    goldModifiers.goldDropFactorMin = modifiers["MinRange"].asFloat();
    goldModifiers.goldDropFactorMax = modifiers["MaxRange"].asFloat();
}

void ConfigFileReader::loadXPModifiers(XPModifiers &xpModifiers) {
    Json::Value& modifiers = obj["XPModifiers"];
    xpModifiers.attackXPModifier = modifiers["AttackXPModifier"].asUInt();
    xpModifiers.killXPMinRange = modifiers["MinKillXPModifier"].asFloat();
    xpModifiers.killXPMaxRange = modifiers["MaxKillXPModifier"].asFloat();
    xpModifiers.nextLevelModifier = modifiers["NextLevelModifier"].asFloat();
    xpModifiers.nextLevelFactor = modifiers["NextLevelFactor"].asUInt();
    xpModifiers.killXPModifier = modifiers["KillXPModifier"].asUInt();
}

float ConfigFileReader::loadCritAttackChance() {
    return obj["CritAttackProb"].asFloat();
}

float ConfigFileReader::loadDodgeChance() {
    return obj["DodgeProb"].asFloat();
}

unsigned int ConfigFileReader::loadNewbieLevel() {
    return obj["NewbieLevel"].asUInt();
}

unsigned int ConfigFileReader::loadmaxLevelDif() {
    return obj["MaxLevelDif"].asUInt();
}

unsigned int ConfigFileReader::loadPlayerVisionRange() {
    return obj["PlayerVisionRange"].asUInt();
}

void ConfigFileReader::_getModifiers(Modifiers& modifier, Json::Value& currModifier){
    modifier.health = currModifier["Health"].asUInt();
    modifier.mana = currModifier["Mana"].asUInt();
    modifier.constitution = currModifier["Constitution"].asUInt();
    modifier.intelligence = currModifier["Intelligence"].asUInt();
    modifier.agility = currModifier["Agility"].asUInt();
    modifier.strength = currModifier["Strength"].asUInt();
    modifier.meditationRate = currModifier["MeditationRate"].asUInt();
    modifier.recoveryRate = currModifier["RecoveryRate"].asUInt();
}

void ConfigFileReader::_getMonsterStats(MonsterStats& stats, Json::Value& currMonster){
    stats.health = currMonster["Health"].asUInt();
    stats.damage = currMonster["Damage"].asUInt();
    stats.rangeOfVision = currMonster["VisionRange"].asUInt();
    stats.minLevel = currMonster["LevelMin"].asUInt();
    stats.maxLevel = currMonster["LevelMax"].asUInt();
}

void ConfigFileReader::_getWeaponStats(WeaponStats& stats, Json::Value currWeapon){
    stats.maxDmg = currWeapon["MaxDmg"].asUInt();
    stats.minDmg = currWeapon["MinDmg"].asUInt();
    stats.manaConsumption = currWeapon["ManaConsumption"].asUInt();
    stats.range = currWeapon["Range"].asUInt();
}

void ConfigFileReader::_getClothingStats(ClothingStats& stats, Json::Value
currClothing){
    stats.maxDefense = currClothing["MaxDefense"].asUInt();
    stats.minDefense = currClothing["MinDefense"].asUInt();
}


