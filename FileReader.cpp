//
// Created by ivan on 8/6/20.
//

#include "FileReader.h"

FileReader::FileReader(const std::string& path) {
    file.open(path);
    reader.parse(file, obj);
}

FileReader::~FileReader() {
    file.close();
}

void FileReader::loadClassModifiers(std::vector<Modifiers> &mods) {
    Json::Value& classModifiers = obj["Class"];
    Modifiers currMods;
    for (auto & classModifier : classModifiers) {
       _getModifiers(currMods, classModifier);
       mods.push_back(currMods);
    }
}

void FileReader::loadRaceModifiers(std::vector<Modifiers> &mods) {
    Json::Value& raceModifiers = obj["Race"];
    Modifiers currMods;
    for (auto & raceModifier : raceModifiers) {
        _getModifiers(currMods, raceModifier);
        mods.push_back(currMods);
    }
}

void FileReader::loadWeaponStats(std::vector<WeaponStats>& stats) {
    Json::Value& weapons = obj["Weapon"];
    WeaponStats currStats;
    for (auto & weapon : weapons) {
        _getWeaponStats(currStats, weapon);
        stats.push_back(currStats);
    }
}

void FileReader::loadClothingStats(std::vector<ClothingStats>& stats) {
    Json::Value& clothings = obj["Clothing"];
    ClothingStats currStats;
    for (auto & clothing : clothings) {
        _getClothingStats(currStats, clothing);
        stats.push_back(currStats);
    }
}


void FileReader::loadMonsterStats(std::vector<MonsterStats>& stats) {
    Json::Value& monsterStats = obj["Monster"];
    MonsterStats currStats;
    for (auto & monsterStat : monsterStats) {
        _getMonsterStats(currStats, monsterStat);
        stats.push_back(currStats);
    }
}

void FileReader::loadGoldModifiers(GoldModifiers &goldModifiers) {
    Json::Value& modifiers = obj["GoldModifiers"];
    goldModifiers.safeGoldFactor = modifiers["MaxSafeGoldFactor"].asUInt();
    goldModifiers.safeGoldLevelModifier = modifiers["MaxGoldLevelModifier"]
            .asFloat();
    goldModifiers.goldDropFactorMin = modifiers["MinRange"].asFloat();
    goldModifiers.goldDropFactorMax = modifiers["MaxRange"].asFloat();
}

void FileReader::loadXPModifiers(XPModifiers &xpModifiers) {
    Json::Value& modifiers = obj["XPModifiers"];
    xpModifiers.attackXPModifier = modifiers["AttackXPModifier"].asUInt();
    xpModifiers.killXPMinModifier = modifiers["MinKillXPModifier"].asFloat();
    xpModifiers.killXPMaxModifier = modifiers["MaxKillXPModifier"].asFloat();
    xpModifiers.nextLevelModifier = modifiers["NextLevelModifier"].asFloat();
    xpModifiers.nextLevelFactor = modifiers["NextLevelFactor"].asUInt();
}

float FileReader::loadCritAttackChance() {
    return obj["CritAttackProb"].asFloat();
}

float FileReader::loadDodgeChance() {
    return obj["DodgeProb"].asFloat();
}

unsigned int FileReader::loadNewbieLevel() {
    return obj["NewbieLevel"].asUInt();
}

unsigned int FileReader::loadmaxLevelDif() {
    return obj["MaxLevelDif"].asUInt();
}

unsigned int FileReader::loadPlayerVisionRange() {
    return obj["PlayerVisionRange"].asUInt();
}

void FileReader::_getModifiers(Modifiers& modifier, Json::Value& currModifier){
    modifier.health = currModifier["Health"].asUInt();
    modifier.mana = currModifier["Mana"].asUInt();
    modifier.constitution = currModifier["Constitution"].asUInt();
    modifier.intelligence = currModifier["Intelligence"].asUInt();
    modifier.agility = currModifier["Agility"].asUInt();
    modifier.strength = currModifier["Strength"].asUInt();
    modifier.meditationRate = currModifier["MeditationRate"].asUInt();
}

void FileReader::_getMonsterStats(MonsterStats& stats, Json::Value& currMonster){
    stats.health = currMonster["Health"].asUInt();
    stats.damage = currMonster["Damage"].asUInt();
    stats.rangeOfVision = currMonster["VisionRange"].asUInt();
    stats.minLevel = currMonster["LevelMin"].asUInt();
    stats.maxLevel = currMonster["LevelMax"].asUInt();
}

void FileReader::_getWeaponStats(WeaponStats& stats, Json::Value currWeapon){
    stats.maxDmg = currWeapon["MaxDmg"].asUInt();
    stats.minDmg = currWeapon["MinDmg"].asUInt();
    stats.manaConsumption = currWeapon["ManaConsumption"].asUInt();
    stats.range = currWeapon["Range"].asUInt();
}

void FileReader::_getClothingStats(ClothingStats& stats, Json::Value
currClothing){
    stats.maxDefense = currClothing["MaxDefense"].asUInt();
    stats.minDefense = currClothing["MinDefense"].asUInt();
}


