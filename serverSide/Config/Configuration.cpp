//
// Created by ivan on 8/6/20.
//

#include "Configuration.h"

using namespace GameType;

Configuration& Configuration::getInstance() {
    static Configuration instance;
    return instance;
}

Configuration::Configuration() {
    Config::ConfigFileReader fileReader("config.json");

    fileReader.loadClassModifiers(classModifiers);
    fileReader.loadRaceModifiers(raceModifiers);
    fileReader.loadMonsterStats(monsterStats);

    fileReader.loadWeaponData(weaponData);
    fileReader.loadClothingData(clothingData);

    fileReader.loadGoldModifiers(goldModifiers);
    fileReader.loadXPModifiers(xpModifiers);

    fileReader.loadPotionData(potionData);

    fileReader.loadMonsterSpawnData(maxMonsterAmount, timeBetweenMonsterSpawns,
                                    monsterSpawnAmount);

    initialMerchantGold = fileReader.loadInitialMerchantGold();

    criticalAttackChance = fileReader.loadCritAttackChance();
    dodgeChance = fileReader.loadDodgeChance();

    newbieLevel = fileReader.loadNewbieLevel();
    maxLevelDif = fileReader.loadmaxLevelDif();
    playerSpeed = fileReader.loadPlayerSpeed();
    goldName = "Gold"; /*Lo guardamos por el tema de guardar las referencias a los nombres de los items*/
}

const Config::Modifiers& Configuration::configClassModifiers(Class _class) const {
    return classModifiers.at(_class);
}

const Config::Modifiers& Configuration::configRaceModifiers(Race race) const{
    return raceModifiers.at(race);
}

const Config::MonsterStats& Configuration::configMonsterStats(GameType::Entity monster) const{
    return monsterStats.at(monster);
}

const Config::WeaponData& Configuration::configWeaponData(Weapon weapon) const{
    return weaponData.at(weapon);
}

const Config::ClothingData& Configuration::configClothingData(Clothing clothes) const{
    return clothingData.at(clothes);
}

const Config::GoldModifiers& Configuration::configGoldModifiers() const{
    return goldModifiers;
}

const Config::XPModifiers& Configuration::configXPModifiers() const{
    return xpModifiers;
}

const Config::PotionData& Configuration::configPotionData(Potion potion) const{
    return potionData.at(potion);
}

float Configuration::configCriticalAttackChance() const{
    return criticalAttackChance;
}

float Configuration::configDodgeChance() const{
    return dodgeChance;
}

unsigned int Configuration::configNewbieLevel() const{
    return newbieLevel;
}

unsigned int Configuration::configMaxLevelDif() const{
    return maxLevelDif;
}

unsigned int Configuration::configTimeBetweenMonsterSpawns() const {
    return timeBetweenMonsterSpawns;
}

unsigned int Configuration::configMaxMonsterAmount() const {
    return maxMonsterAmount;
}

unsigned int Configuration::configMonsterSpawnAmount() const {
    return monsterSpawnAmount;
}

unsigned int Configuration::configInitialMerchantGold() const {
    return initialMerchantGold;
}

const std::string& Configuration::configGetGoldName() const {
    return goldName;
}

const std::unordered_map<GameType::Weapon, Config::WeaponData> &
                                Configuration::configAllWeaponsData() {
    return weaponData;
}

const std::unordered_map<GameType::Clothing, Config::ClothingData> &
                                Configuration::configAllClothingData() {
    return clothingData;
}

const std::unordered_map<GameType::Potion, Config::PotionData> &
                                Configuration::configAllPotionsData() {
    return potionData;
}

unsigned int Configuration::configPlayerSpeed() const {
    return playerSpeed;
}
