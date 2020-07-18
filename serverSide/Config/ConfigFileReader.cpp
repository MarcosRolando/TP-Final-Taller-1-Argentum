//
// Created by ivan on 8/6/20.
//

#include "ConfigFileReader.h"
#include "../../libs/TPException.h"
#include <memory>

using namespace GameType;

Config::ConfigFileReader::ConfigFileReader(const std::string& path) :
    classes{{"Warrior", WARRIOR}, {"Wizard", WIZARD}, {"Paladin", PALADIN},
           {"Cleric", CLERIC}},
    races{{"Human", HUMAN}, {"Elf", ELF},{"Dwarf", DWARF}, {"Gnome", GNOME}},
    monsters{{"Skeleton", SKELETON}, {"Zombie", ZOMBIE},{"Spider", SPIDER}, {"Goblin", GOBLIN}},
    weapons{{"Longsword", LONGSWORD},{"Axe", AXE}, {"Warhammer", WARHAMMER},
            {"AshRod", ASH_ROD}, {"ElvenFlute", ELVEN_FLUTE}, {"LinkedStaff", LINKED_STAFF},
            {"SimpleBow", SIMPLE_BOW}, {"CompositeBow", COMPOSITE_BOW}, {"GnarledStaff", GNARLED_STAFF},
            {"Fist", FIST}},
    clothing{{"CommonClothing", COMMON_CLOTHING},{"LeatherArmor", LEATHER_ARMOR}, {"PlateArmor", PLATE_ARMOR},
            {"BlueTunic", BLUE_TUNIC}, {"Hood", HOOD}, {"IronHelmet", IRON_HELMET},
            {"TurtleShield", TURTLE_SHIELD}, {"IronShield", IRON_SHIELD}, {"MagicHat", MAGIC_HAT},
            {"NoHelmet", NO_HELMET}, {"NoShield", NO_SHIELD}},
    potions {{"HealthPotion", HEALTH_POTION}, {"ManaPotion", MANA_POTION}} {

    std::ifstream file(path);
    if (!file.is_open()) {
        throw TPException("No se pudo abrir el arcvio de Config,"
                          " asegurese de que el archivo existe!");
    }

    try {
        file >> obj;
    } catch (...) {
        throw TPException("Fallo el parseo del Config de Json!");
    }
}

void Config::ConfigFileReader::loadClassModifiers(std::unordered_map<Class, Modifiers>& mods) {
    Json::Value& classModifiers = obj["Class"];
    Modifiers currMods{};
    for (auto & classModifier : classModifiers) {
       _getModifiers(currMods, classModifier);
        currMods.meditationRate = classModifier["MeditationRate"].asUInt();
        currMods.recoveryRate = 0;
        mods.emplace(classes.at(classModifier["Name"].asString()), currMods);
    }
}

void Config::ConfigFileReader::loadRaceModifiers(std::unordered_map<Race, Modifiers>& mods) {
    Json::Value& raceModifiers = obj["Race"];
    Modifiers currMods{};
    for (auto & raceModifier : raceModifiers) {
        _getModifiers(currMods, raceModifier);
        currMods.recoveryRate = raceModifier["RecoveryRate"].asUInt();
        currMods.meditationRate = 0;
        mods.emplace(races.at(raceModifier["Name"].asString()), currMods);
    }
}

void Config::ConfigFileReader::loadWeaponData(std::unordered_map<Weapon, WeaponData>& stats) {
    Json::Value& weaponsStats = obj["Weapon"];
    WeaponData currStats{};
    for (auto & weaponStat : weaponsStats) {
        _getWeaponData(currStats, weaponStat);
        stats.emplace(weapons.at(weaponStat["Name"].asString()), currStats);
    }
}

void Config::ConfigFileReader::loadClothingData(std::unordered_map<Clothing, ClothingData>& stats) {
    Json::Value& clothingsStats = obj["Clothing"];
    ClothingData currStats{};
    for (auto & clothingStat : clothingsStats) {
        _getClothingData(currStats, clothingStat);
        stats.emplace(clothing.at(clothingStat["Name"].asString()), currStats);
    }
}

void Config::ConfigFileReader::loadPotionData(std::unordered_map<Potion, PotionData>& stats) {
    Json::Value& potionData = obj["Potion"];
    PotionData currPotion{};
    for (auto & potion : potionData) {
        _getPotionData(currPotion, potion);
        stats.emplace(potions.at(potion["Name"].asString()), currPotion);
    }
}


void Config::ConfigFileReader::loadMonsterStats(std::unordered_map<GameType::Entity, MonsterStats>& stats) {
    Json::Value& monsterStats = obj["Monster"];
    MonsterStats currStats{};
    for (auto & monsterStat : monsterStats) {
        _getMonsterStats(currStats, monsterStat);
        stats.emplace(monsters.at(monsterStat["Name"].asString()), currStats);
    }
}

void Config::ConfigFileReader::loadGoldModifiers(GoldModifiers& goldModifiers) {
    Json::Value& modifiers = obj["GoldModifiers"];
    goldModifiers.safeGoldFactor = modifiers["MaxSafeGoldFactor"].asUInt();
    goldModifiers.safeGoldLevelModifier = modifiers["MaxGoldLevelModifier"]
            .asFloat();
    goldModifiers.goldDropFactorMin = modifiers["MinRange"].asFloat();
    goldModifiers.goldDropFactorMax = modifiers["MaxRange"].asFloat();
}

void Config::ConfigFileReader::loadXPModifiers(XPModifiers& xpModifiers) {
    Json::Value& modifiers = obj["XPModifiers"];
    xpModifiers.attackXPModifier = modifiers["AttackXPModifier"].asUInt();
    xpModifiers.killXPMinRange = modifiers["MinKillXPModifier"].asFloat();
    xpModifiers.killXPMaxRange = modifiers["MaxKillXPModifier"].asFloat();
    xpModifiers.nextLevelModifier = modifiers["NextLevelModifier"].asFloat();
    xpModifiers.nextLevelFactor = modifiers["NextLevelFactor"].asUInt();
    xpModifiers.killXPModifier = modifiers["KillXPModifier"].asUInt();
}

float Config::ConfigFileReader::loadCritAttackChance() {
    return obj["CritAttackProb"].asFloat();
}

float Config::ConfigFileReader::loadDodgeChance() {
    return obj["DodgeProb"].asFloat();
}

unsigned int Config::ConfigFileReader::loadNewbieLevel() {
    return obj["NewbieLevel"].asUInt();
}

unsigned int Config::ConfigFileReader::loadmaxLevelDif() {
    return obj["MaxLevelDif"].asUInt();
}

void Config::ConfigFileReader::_getModifiers(Modifiers& modifier, Json::Value& currModifier){
    modifier.lifeMultiplier = currModifier["Life"].asUInt();
    modifier.manaMultiplier = currModifier["Mana"].asUInt();
    modifier.constitution = currModifier["Constitution"].asUInt();
    modifier.intelligence = currModifier["Intelligence"].asUInt();
    modifier.agility = currModifier["Agility"].asUInt();
    modifier.strength = currModifier["Strength"].asUInt();
}

void Config::ConfigFileReader::_getMonsterStats(MonsterStats& stats, Json::Value& currMonster){
    stats.life = currMonster["Life"].asUInt();
    stats.damage = currMonster["Damage"].asUInt();
    stats.rangeOfVision = currMonster["VisionRange"].asUInt();
    stats.minLevel = currMonster["LevelMin"].asUInt();
    stats.maxLevel = currMonster["LevelMax"].asUInt();
    stats.constitution = currMonster["Constitution"].asUInt();
    stats.agility = currMonster["Agility"].asUInt();
    stats.strength = currMonster["Strength"].asUInt();
    stats.reactionSpeed = currMonster["ReactionSpeed"].asUInt();
    stats.speed = currMonster["Speed"].asUInt();
}

void Config::ConfigFileReader::_getWeaponData(WeaponData& stats, Json::Value& currWeapon){
    stats.name = currWeapon["Name"].asString();
    stats.maxDmg = currWeapon["MaxDmg"].asInt();
    stats.minDmg = currWeapon["MinDmg"].asInt();
    stats.manaConsumption = currWeapon["ManaConsumption"].asUInt();
    stats.range = currWeapon["Range"].asUInt();
    stats.price = currWeapon["Price"].asUInt();
}

void Config::ConfigFileReader::_getClothingData(ClothingData& stats, Json::Value&
                                        currClothing){
    stats.name = currClothing["Name"].asString();
    stats.maxDefense = currClothing["MaxDefense"].asUInt();
    stats.minDefense = currClothing["MinDefense"].asUInt();
    stats.price = currClothing["Price"].asUInt();
}

void Config::ConfigFileReader::_getPotionData(PotionData& stats, Json::Value&
                                        currPotion){
    stats.name = currPotion["Name"].asString();
    stats.recoveryValue = currPotion["RecoveryValue"].asUInt();
    stats.price = currPotion["Price"].asUInt();
}

void Config::ConfigFileReader::loadMonsterSpawnData(unsigned int &maxMonsterAmount,
                                               unsigned int &timeBetweenMonsterSpawns,
                                               unsigned int &monsterSpawnAmount) {
    Json::Value& data = obj["MonsterSpawnData"];
    maxMonsterAmount = data["MaxAmount"].asUInt();
    timeBetweenMonsterSpawns = data["TimeBetweenSpawns"].asUInt();
    monsterSpawnAmount = data["SpawnAmount"].asUInt();
}

unsigned int Config::ConfigFileReader::loadInitialMerchantGold() {
    return obj["InitialMerchantGold"].asUInt();
}

unsigned int Config::ConfigFileReader::loadPlayerSpeed() {
    return obj["PlayerSpeed"].asUInt();
}

double Config::ConfigFileReader::loadTimeForPlayerRecovery() {
    return obj["TimeForPlayerRecoveryInSeconds"].asUInt();
}
