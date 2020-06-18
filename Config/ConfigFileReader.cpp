//
// Created by ivan on 8/6/20.
//

#include "ConfigFileReader.h"
#include "../TPException.h"

using namespace Config;

ConfigFileReader::ConfigFileReader(const std::string& path) :
    classes{{"Warrior", WARRIOR}, {"Wizard", WIZARD}, {"Paladin", PALADIN},
           {"Cleric", CLERIC}},
    races{{"Human", HUMAN}, {"Elf", ELF},{"Dwarf", DWARF}, {"Gnome", GNOME}},
    monsters{{"Skeleton", SKELETON}, {"Zombie", ZOMBIE},{"Spider", SPIDER}, {"Goblin", GOBLIN}},
    weapons{{"Longsword", LONGSWORD},{"Axe", AXE}, {"Warhammer", WARHAMMER},
            {"AshRod", ASH_ROD}, {"ElvenFlute", ELVEN_FLUTE}, {"LinkedStaff", LINKED_STAFF},
            {"SimpleBow", SIMPLE_BOW}, {"CompoundBow", COMPOSITE_BOW}, {"GnarledStaff", GNARLED_STAFF}},
    clothing{{"Longsword", COMMON_CLOTHING},{"Axe", LEATHER_ARMOR}, {"Warhammer", PLATE_ARMOR},
            {"AshRod", BLUE_TUNIC}, {"ElvenFlute", HOOD}, {"LinkedStaff", IRON_HELMET},
            {"SimpleBow", TURTLE_SHIELD}, {"CompoundBow", IRON_SHIELD}, {"GnarledStaff", MAGIC_HAT}} {

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

void Config::ConfigFileReader::loadClassModifiers(std::unordered_map<Class, Modifiers>& mods) {
    Json::Value& classModifiers = obj["Class"];
    Modifiers currMods{};
    for (auto & classModifier : classModifiers) {
       _getModifiers(currMods, classModifier);
       mods.emplace(classes.at(classModifier["Name"].asString()), currMods);
    }
}

void ConfigFileReader::loadRaceModifiers(std::unordered_map<Race, Modifiers>& mods) {
    Json::Value& raceModifiers = obj["Race"];
    Modifiers currMods{};
    for (auto & raceModifier : raceModifiers) {
        _getModifiers(currMods, raceModifier);
        mods.emplace(races.at(raceModifier["Name"].asString()), currMods);
    }
}

void ConfigFileReader::loadWeaponData(std::unordered_map<Weapon, WeaponData>& stats) {
    Json::Value& weaponsStats = obj["Weapon"];
    WeaponData currStats{};
    for (auto & weaponStat : weaponsStats) {
        _getWeaponData(currStats, weaponStat);
        stats.emplace(weapons.at(weaponStat["Type"].asString()), currStats);
    }
}

void ConfigFileReader::loadClothingData(std::unordered_map<Clothing, ClothingData>& stats) {
    Json::Value& clothingsStats = obj["Clothing"];
    ClothingData currStats{};
    for (auto & clothingStat : clothingsStats) {
        _getClothingData(currStats, clothingStat);
        stats.emplace(clothing.at(clothingStat["Type"].asString()), currStats);
    }
}


void ConfigFileReader::loadMonsterStats(std::unordered_map<Monster, MonsterStats>& stats) {
    Json::Value& monsterStats = obj["Monster"];
    MonsterStats currStats{};
    for (auto & monsterStat : monsterStats) {
        _getMonsterStats(currStats, monsterStat);
        stats.emplace(monsters.at(monsterStat["Name"].asString()), currStats);
    }
}

void ConfigFileReader::loadGoldModifiers(GoldModifiers& goldModifiers) {
    Json::Value& modifiers = obj["GoldModifiers"];
    goldModifiers.safeGoldFactor = modifiers["MaxSafeGoldFactor"].asUInt();
    goldModifiers.safeGoldLevelModifier = modifiers["MaxGoldLevelModifier"]
            .asFloat();
    goldModifiers.goldDropFactorMin = modifiers["MinRange"].asFloat();
    goldModifiers.goldDropFactorMax = modifiers["MaxRange"].asFloat();
}

void ConfigFileReader::loadXPModifiers(XPModifiers& xpModifiers) {
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
    modifier.lifeMultiplier = currModifier["Health"].asUInt();
    modifier.manaMultiplier = currModifier["Mana"].asUInt();
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

void ConfigFileReader::_getWeaponData(WeaponData& stats, Json::Value& currWeapon){
    stats.name = currWeapon["Name"].asString();
    stats.maxDmg = currWeapon["MaxDmg"].asUInt();
    stats.minDmg = currWeapon["MinDmg"].asUInt();
    stats.manaConsumption = currWeapon["ManaConsumption"].asUInt();
    stats.range = currWeapon["Range"].asUInt();
    stats.price = currWeapon["Price"].asUInt();
}

void ConfigFileReader::_getClothingData(ClothingData& stats, Json::Value&
                                        currClothing){
    stats.name = currClothing["Name"].asString();
    stats.maxDefense = currClothing["MaxDefense"].asUInt();
    stats.minDefense = currClothing["MinDefense"].asUInt();
    stats.price = currClothing["Price"].asUInt();
}