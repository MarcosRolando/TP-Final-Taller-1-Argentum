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

void FileReader::getClassModifiers(std::vector<Modifiers> &mods) {
    Json::Value& classModifiers = obj["Class"];
    Modifiers currMods;
    for (auto & classModifier : classModifiers) {
       _getModifiers(currMods, classModifier);
       mods.push_back(currMods);
    }
}

void FileReader::getRaceModifiers(std::vector<Modifiers> &mods) {
    Json::Value& raceModifiers = obj["Race"];
    Modifiers currMods;
    for (auto & raceModifier : raceModifiers) {
        _getModifiers(currMods, raceModifier);
        mods.push_back(currMods);
    }
}

void FileReader::getMonsterStats(std::vector<MonsterStats>& stats) {
    Json::Value& monsterStats = obj["Monster"];
    MonsterStats currStats;
    for (auto & monsterStat : monsterStats) {
        _getStats(currStats, monsterStat);
        stats.push_back(currStats);
    }
}

void FileReader::getGoldModifiers(GoldModifiers &goldModifiers) {
    Json::Value& modifiers = obj["GoldModifiers"];
    goldModifiers.safeGoldFactor = modifiers["MaxSafeGoldFactor"].asUInt();
    goldModifiers.safeGoldLevelModifier = modifiers["MaxGoldLevelModifier"]
            .asFloat();
    goldModifiers.goldDropFactorMin = modifiers["MinRange"].asFloat();
    goldModifiers.goldDropFactorMax = modifiers["MaxRange"].asFloat();
}

void FileReader::getXPModifiers(XPModifiers &xpModifiers) {
    Json::Value& modifiers = obj["XPModifiers"];
    xpModifiers.attackXPModifier = modifiers["AttackXPModifier"].asUInt();
    xpModifiers.killXPMinModifier = modifiers["MinKillXPModifier"].asFloat();
    xpModifiers.killXPMaxModifier = modifiers["MaxKillXPModifier"].asFloat();
    xpModifiers.nextLevelModifier = modifiers["NextLevelModifier"].asFloat();
    xpModifiers.nextLevelFactor = modifiers["NextLevelFactor"].asUInt();
}

float FileReader::getCritAttackChance() {
    return obj["CritAttackProb"].asFloat();
}

float FileReader::getDodgeChance() {
    return obj["DodgeProb"].asFloat();
}

unsigned int FileReader::getNewbieLevel() {
    return obj["NewbieLevel"].asUInt();
}

unsigned int FileReader::getmaxLevelDif() {
    return obj["MaxLevelDif"].asUInt();
}

unsigned int FileReader::getPlayerVisionRange() {
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

void FileReader::_getStats(MonsterStats& stats, Json::Value& currStat){
    stats.health = currStat["Health"].asUInt();
    stats.damage = currStat["Damage"].asUInt();
    stats.rangeOfVision = currStat["VisionRange"].asUInt();
    stats.maxLevel = currStat["LevelMin"].asUInt();
    stats.minLevel = currStat["LevelMax"].asUInt();
}