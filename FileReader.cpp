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

void FileReader::getClassModifiers(Modifiers& modifier, const std::string& type) {
    Json::Value& classModifiers = obj["Class"];
    for (auto & classModifier : classModifiers) {
       if (classModifier["Name"].asString() == type){
           _getModifiers(modifier, classModifier);
       }
    }
}

void FileReader::getRaceModifiers(Modifiers& modifier, const std::string& type) {
    Json::Value& raceModifiers = obj["Race"];
    for (auto & raceModifier : raceModifiers) {
        if (raceModifier["Name"].asString() == type){
            _getModifiers(modifier, raceModifier);
        }
    }
}

void FileReader::getMonsterStats(MonsterStats& stats, const std::string& type) {
    Json::Value& monsterStats = obj["Monster"];
    for (auto & monsterStat : monsterStats) {
        if (monsterStat["Name"].asString() == type){
            _getStats(stats, monsterStat);
        }
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