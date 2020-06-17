//
// Created by ivan on 8/6/20.
//

#include "Configuration.h"

Configuration& Configuration::getInstance() {
    static Configuration instance;
    return instance;
}

Configuration::Configuration() {
    ConfigFileReader fileReader("../config.json");

    fileReader.loadClassModifiers(classModifiers);
    fileReader.loadRaceModifiers(raceModifiers);
    fileReader.loadMonsterStats(monsterStats);

    fileReader.loadWeaponStats(weaponStats);
    fileReader.loadClothingStats(clothingStats);

    fileReader.loadGoldModifiers(goldModifiers);
    fileReader.loadXPModifiers(xpModifiers);

    criticalAttackChance = fileReader.loadCritAttackChance();
    dodgeChance = fileReader.loadDodgeChance();

    newbieLevel = fileReader.loadNewbieLevel();
    maxLevelDif = fileReader.loadmaxLevelDif();
    playerVisionRange = fileReader.loadPlayerVisionRange();
}

Modifiers Configuration::configMageModifiers() const{
    return classModifiers[MAGE];
}

Modifiers Configuration::configClericModifiers() const{
    return classModifiers[CLERIC];
}

Modifiers Configuration::configPaladinModifiers() const{
    return classModifiers[PALADIN];
}

Modifiers Configuration::configWarriorModifiers() const{
    return classModifiers[WARRIOR];
}

Modifiers Configuration::configHumanModifiers() const{
    return raceModifiers[HUMAN];
}

Modifiers Configuration::configElfModifiers() const{
    return raceModifiers[ELF];
}

Modifiers Configuration::configDwarfModifiers() const{
    return raceModifiers[DWARF];
}

Modifiers Configuration::configGnomeModifiers() const{
    return raceModifiers[GNOME];
}

MonsterStats Configuration::configSkeletonStats() const{
    return monsterStats[SKELETON];
}

MonsterStats Configuration::configZombieStats() const{
    return monsterStats[ZOMBIE];
}

MonsterStats Configuration::configSpiderStats() const{
    return monsterStats[SPIDER];
}

MonsterStats Configuration::configGoblinStats() const{
    return monsterStats[GOBLIN];
}

WeaponStats Configuration::configLongSwordStats() const{
    return weaponStats[LONGSWORD];
}

WeaponStats Configuration::configAxeStats() const{
    return weaponStats[AXE];
}

WeaponStats Configuration::configWarhammerStats() const{
    return weaponStats[WARHAMMER];
}

WeaponStats Configuration::configAshRodStats() const{
    return weaponStats[ASH_ROD];
}

WeaponStats Configuration::configElvenFluteStats() const{
    return weaponStats[ELVEN_FLUTE];
}

WeaponStats Configuration::configLinkedStaffStats() const{
    return weaponStats[LINKED_STAFF];
}

WeaponStats Configuration::configSimpleBowStats() const{
    return weaponStats[SIMPLE_BOW];
}

WeaponStats Configuration::configCompoundBowStats() const{
    return weaponStats[COMPOUND_BOW];
}

ClothingStats Configuration::configCommonClothingStats() const{
    return clothingStats[COMMON_CLOTHING];
}

ClothingStats Configuration::configLeatherArmorStats() const{
    return clothingStats[LEATHER_ARMOR];
}

ClothingStats Configuration::configPlateArmorStats() const{
    return clothingStats[PLATE_ARMOR];
}

ClothingStats Configuration::configBlueTunicStats() const{
    return clothingStats[BLUE_TUNIC];
}

ClothingStats Configuration::configHoodStats() const{
    return clothingStats[HOOD];
}

ClothingStats Configuration::configIronHelmetStats() const{
    return clothingStats[IRON_HELMET];
}

ClothingStats Configuration::configTurtleShieldStats() const{
    return clothingStats[TURTLE_SHIELD];
}

ClothingStats Configuration::configIronShieldStats() const{
    return clothingStats[IRON_SHIELD];
}

ClothingStats Configuration::configMagicHatStats() const{
    return clothingStats[MAGIC_HAT];
}


GoldModifiers Configuration::configGoldModifiers() const{
    return goldModifiers;
}

XPModifiers Configuration::configXPModifiers() const{
    return xpModifiers;
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

unsigned int Configuration::configPlayerVisionRange() const {
    return playerVisionRange;
}
