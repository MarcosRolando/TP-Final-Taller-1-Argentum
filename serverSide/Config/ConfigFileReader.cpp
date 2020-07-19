//
// Created by ivan on 8/6/20.
//

#include "ConfigFileReader.h"
#include "../../libs/TPException.h"
#include <memory>

using namespace GameType;
using json = nlohmann::json;

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
        throw TPException("Could not open Config File, check whether"
                          " it exists or not");
    }
    try {
        file >> obj;
    } catch (...) {
        throw TPException("Json Config File parsing failed!");
    }
}

void Config::ConfigFileReader::loadClassModifiers(std::unordered_map<Class, Modifiers>& mods) {
    json& classModifiers = obj["Class"];
    Modifiers currMods{};
    for (auto & classModifier : classModifiers) {
       _getModifiers(currMods, classModifier);
        currMods.meditationRate = classModifier["MeditationRate"].get<uint>();
        currMods.recoveryRate = 0;
        mods.emplace(classes.at(classModifier["Name"].get<std::string>()), currMods);
    }
}

void Config::ConfigFileReader::loadRaceModifiers(std::unordered_map<Race, Modifiers>& mods) {
    json& raceModifiers = obj["Race"];
    Modifiers currMods{};
    for (auto & raceModifier : raceModifiers) {
        _getModifiers(currMods, raceModifier);
        currMods.recoveryRate = raceModifier["RecoveryRate"].get<uint>();
        currMods.meditationRate = 0;
        mods.emplace(races.at(raceModifier["Name"].get<std::string>()), currMods);
    }
}

void Config::ConfigFileReader::loadWeaponData(std::unordered_map<Weapon, WeaponData>& stats) {
    json& weaponsStats = obj["Weapon"];
    WeaponData currStats{};
    for (auto & weaponStat : weaponsStats) {
        _getWeaponData(currStats, weaponStat);
        stats.emplace(weapons.at(weaponStat["Name"].get<std::string>()), currStats);
    }
}

void Config::ConfigFileReader::loadClothingData(std::unordered_map<Clothing, ClothingData>& stats) {
    json& clothingsStats = obj["Clothing"];
    ClothingData currStats{};
    for (auto & clothingStat : clothingsStats) {
        _getClothingData(currStats, clothingStat);
        stats.emplace(clothing.at(clothingStat["Name"].get<std::string>()), currStats);
    }
}

void Config::ConfigFileReader::loadPotionData(std::unordered_map<Potion, PotionData>& stats) {
    json& potionData = obj["Potion"];
    PotionData currPotion{};
    for (auto & potion : potionData) {
        _getPotionData(currPotion, potion);
        stats.emplace(potions.at(potion["Name"].get<std::string>()), currPotion);
    }
}


void Config::ConfigFileReader::loadMonsterStats(std::unordered_map<GameType::Entity, MonsterStats>& stats) {
    json& monsterStats = obj["Monster"];
    MonsterStats currStats{};
    for (auto & monsterStat : monsterStats) {
        _getMonsterStats(currStats, monsterStat);
        stats.emplace(monsters.at(monsterStat["Name"].get<std::string>()), currStats);
    }
}

void Config::ConfigFileReader::loadGoldModifiers(GoldModifiers& goldModifiers) {
    json& modifiers = obj["GoldModifiers"];
    goldModifiers.safeGoldFactor = modifiers["MaxSafeGoldFactor"].get<uint>();
    goldModifiers.safeGoldLevelModifier = modifiers["MaxGoldLevelModifier"]
            .get<float>();
    goldModifiers.goldDropFactorMin = modifiers["MinRange"].get<float>();
    goldModifiers.goldDropFactorMax = modifiers["MaxRange"].get<float>();
}

void Config::ConfigFileReader::loadXPModifiers(XPModifiers& xpModifiers) {
    json& modifiers = obj["XPModifiers"];
    xpModifiers.attackXPModifier = modifiers["AttackXPModifier"].get<unsigned int>();
    xpModifiers.killXPMinRange = modifiers["MinKillXPModifier"].get<float>();
    xpModifiers.killXPMaxRange = modifiers["MaxKillXPModifier"].get<float>();
    xpModifiers.nextLevelModifier = modifiers["NextLevelModifier"].get<float>();
    xpModifiers.nextLevelFactor = modifiers["NextLevelFactor"].get<unsigned int>();
    xpModifiers.killXPModifier = modifiers["KillXPModifier"].get<unsigned int>();
}

float Config::ConfigFileReader::loadCritAttackChance() {
    return obj["CritAttackProb"].get<float>();
}

float Config::ConfigFileReader::loadDodgeChance() {
    return obj["DodgeCoeff"].get<float>();
}

unsigned int Config::ConfigFileReader::loadNewbieLevel() {
    return obj["NewbieLevel"].get<unsigned int>();
}

unsigned int Config::ConfigFileReader::loadmaxLevelDif() {
    return obj["MaxLevelDif"].get<unsigned int>();
}

void Config::ConfigFileReader::_getModifiers(Modifiers& modifier, json& currModifier){
    modifier.lifeMultiplier = currModifier["Life"].get<unsigned int>();
    modifier.manaMultiplier = currModifier["Mana"].get<unsigned int>();
    modifier.constitution = currModifier["Constitution"].get<unsigned int>();
    modifier.intelligence = currModifier["Intelligence"].get<unsigned int>();
    modifier.agility = currModifier["Agility"].get<unsigned int>();
    modifier.strength = currModifier["Strength"].get<unsigned int>();
}

void Config::ConfigFileReader::_getMonsterStats(MonsterStats& stats, json& currMonster){
    stats.life = currMonster["Life"].get<unsigned int>();
    stats.damage = currMonster["Damage"].get<unsigned int>();
    stats.rangeOfVision = currMonster["VisionRange"].get<unsigned int>();
    stats.minLevel = currMonster["LevelMin"].get<unsigned int>();
    stats.maxLevel = currMonster["LevelMax"].get<unsigned int>();
    stats.constitution = currMonster["Constitution"].get<unsigned int>();
    stats.agility = currMonster["Agility"].get<unsigned int>();
    stats.strength = currMonster["Strength"].get<unsigned int>();
    stats.reactionSpeed = currMonster["ReactionSpeed"].get<unsigned int>();
    stats.speed = currMonster["Speed"].get<unsigned int>();
}

void Config::ConfigFileReader::_getWeaponData(WeaponData& stats, json& currWeapon){
    stats.name = currWeapon["Name"].get<std::string>();
    stats.maxDmg = currWeapon["MaxDmg"].get<int>();
    stats.minDmg = currWeapon["MinDmg"].get<int>();
    stats.manaConsumption = currWeapon["ManaConsumption"].get<unsigned int>();
    stats.range = currWeapon["Range"].get<unsigned int>();
    stats.price = currWeapon["Price"].get<unsigned int>();
}

void Config::ConfigFileReader::_getClothingData(ClothingData& stats, json&
                                        currClothing){
    stats.name = currClothing["Name"].get<std::string>();
    stats.maxDefense = currClothing["MaxDefense"].get<unsigned int>();
    stats.minDefense = currClothing["MinDefense"].get<unsigned int>();
    stats.price = currClothing["Price"].get<unsigned int>();
}

void Config::ConfigFileReader::_getPotionData(PotionData& stats, json&
                                        currPotion){
    stats.name = currPotion["Name"].get<std::string>();
    stats.recoveryValue = currPotion["RecoveryValue"].get<unsigned int>();
    stats.price = currPotion["Price"].get<unsigned int>();
}

void Config::ConfigFileReader::loadMonsterSpawnData(unsigned int &maxMonsterAmount,
                                               unsigned int &timeBetweenMonsterSpawns,
                                               unsigned int &monsterSpawnAmount) {
    json& data = obj["MonsterSpawnData"];
    maxMonsterAmount = data["MaxAmount"].get<unsigned int>();
    timeBetweenMonsterSpawns = data["TimeBetweenSpawns"].get<unsigned int>();
    monsterSpawnAmount = data["SpawnAmount"].get<unsigned int>();
}

unsigned int Config::ConfigFileReader::loadInitialMerchantGold() {
    return obj["InitialMerchantGold"].get<unsigned int>();
}

unsigned int Config::ConfigFileReader::loadPlayerSpeed() {
    return obj["PlayerSpeed"].get<unsigned int>();
}

double Config::ConfigFileReader::loadTimeForPlayerRecovery() {
    return obj["TimeForPlayerRecoveryInSeconds"].get<unsigned int>();
}

std::string Config::ConfigFileReader::loadPort() {
    return obj["Port"].get<std::string>();
}

std::string Config::ConfigFileReader::loadMapPath() {
    return obj["MapPath"].get<std::string>();
}

std::string Config::ConfigFileReader::loadSavePath() {
    return obj["SavePath"].get<std::string>();
}

std::string Config::ConfigFileReader::loadIndexPath() {
    return obj["IndexPath"].get<std::string>();
}
