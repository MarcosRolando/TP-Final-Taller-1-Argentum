//
// Created by ivan on 8/6/20.
//

#include "FileReader.h"

FileReader::FileReader(std::string path) {
    file.open(path);
    reader.parse(file, obj);
}

FileReader::~FileReader() {
    file.close();
}

void FileReader::getClassModifiers(Modifiers& modifier, std::string type) {
    Json::Value& classModifiers = obj["Class"];
    for (auto & classModifier : classModifiers) {
       if (classModifier["Name"].asString() == type){
           modifier.health = classModifier["Health"].asUInt();
           modifier.mana = classModifier["Mana"].asUInt();
           modifier.constitution = classModifier["Constitution"].asUInt();
           modifier.intelligence = classModifier["Intelligence"].asUInt();
           modifier.agility = classModifier["Agility"].asUInt();
           modifier.strength = classModifiers["Strength"].asUInt();
           modifier.meditationRate = classModifiers["MeditationRate"].asUInt();
       }
    }
}

void FileReader::getRaceModifiers(Modifiers& modifier, std::string type) {
    Json::Value& classModifiers = obj["Race"];
    for (auto & classModifier : classModifiers) {//Meter el for en una
        // funcion aparte xq es lo mismo para race y class
        if (classModifier["Name"].asString() == type){
            modifier.health = classModifier["Health"].asUInt();
            modifier.mana = classModifier["Mana"].asUInt();
            modifier.constitution = classModifier["Constitution"].asUInt();
            modifier.intelligence = classModifier["Intelligence"].asUInt();
            modifier.agility = classModifier["Agility"].asUInt();
            modifier.strength = classModifiers["Strength"].asUInt();
            modifier.meditationRate = classModifiers["MeditationRate"].asUInt();
        }
    }
}

void FileReader::getMonsterStats(MonsterStats& stats, std::string type) {
    Json::Value& monsterStats = obj["Monster"];
    for (auto & monsterStat : monsterStats) {//Meter el for en una
        // funcion aparte xq es lo mismo para race y class
        if (monsterStat["Name"].asString() == type){
            stats.health = monsterStat["Health"].asUInt();
            stats.damage = monsterStat["Damage"].asUInt();
            stats.rangeOfVision = monsterStat["VisionRange"].asUInt();
            stats.maxLevel = monsterStat["LevelMin"].asUInt();
            stats.minLevel = monsterStat["LevelMax"].asUInt();
        }
    }
}

void FileReader::getGoldModifiers(GoldModifiers &goldModifiers) {

}

void FileReader::getXPModifiers(XPModifiers &xpModifiers) {

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

unsigned int FileReader::getInventorySize() {
    return obj["InventorySize"].asUInt();
}

