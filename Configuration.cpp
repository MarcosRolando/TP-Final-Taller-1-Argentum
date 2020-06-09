//
// Created by ivan on 8/6/20.
//

#include "Configuration.h"


Configuration &Configuration::getInstance() {
    static Configuration instance;
    return instance;
}

Configuration::Configuration() {
    FileReader fileReader("../config.json");
    fileReader.getClassModifiers(mageModifiers, "Mage");
    fileReader.getClassModifiers(clericModifiers, "Cleric");
    fileReader.getClassModifiers(paladinModifiers, "Paladin");
    fileReader.getClassModifiers(warriorModifiers, "Warrior");

    fileReader.getRaceModifiers(humanModifiers, "Human");
    fileReader.getRaceModifiers(elfModifiers, "Elf");
    fileReader.getRaceModifiers(dwarfModifiers, "Dwarf");
    fileReader.getRaceModifiers(gnomeModifiers, "Gnome");

    fileReader.getMonsterStats(skeletonStats, "Skeleton");
    fileReader.getMonsterStats(zombieStats, "Zombie");
    fileReader.getMonsterStats(goblinStats, "Goblin");
    fileReader.getMonsterStats(spiderStats, "Spider");

    fileReader.getGoldModifiers(goldModifiers);
    fileReader.getXPModifiers(xpModifiers);

    criticalAttackChance = fileReader.getCritAttackChance();
    dodgeChance = fileReader.getDodgeChance();

    newbieLevel = fileReader.getNewbieLevel();
    maxLevelDif =  fileReader.getmaxLevelDif();

    inventorySize = fileReader.getInventorySize();
}

Modifiers Configuration::getMageModifiers(){
    return mageModifiers;
}

Modifiers Configuration::getClericModifiers(){
    return clericModifiers;
}

Modifiers Configuration::getPaladinModifiers(){
    return paladinModifiers;
}

Modifiers Configuration::getWarriorModifiers(){
    return warriorModifiers;
}

Modifiers Configuration::getHumanModifiers(){
    return humanModifiers;
}

Modifiers Configuration::getElfModifiers(){
    return elfModifiers;
}

Modifiers Configuration::getDwarfModifiers(){
    return dwarfModifiers;
}

Modifiers Configuration::getGnomeModifiers(){
    return gnomeModifiers;
}

MonsterStats Configuration::getSkeletonStats(){
    return skeletonStats;
}

MonsterStats Configuration::getSpiderStats(){
    return spiderStats;
}

MonsterStats Configuration::getZombieStats(){
    return zombieStats;
}

MonsterStats Configuration::getGoblinStats(){
    return goblinStats;
}

GoldModifiers Configuration::getGoldModifiers(){
    return goldModifiers;
}

XPModifiers Configuration::getXPModifiers(){
    return xpModifiers;
}

float Configuration::getCriticalAttackChance(){
    return criticalAttackChance;
}

float Configuration::getDodgeChance(){
    return dodgeChance;
}

unsigned int Configuration::getNewbieLevel(){
    return newbieLevel;
}

unsigned int Configuration::getMaxLevelDif(){
    return maxLevelDif;
}

unsigned int Configuration::getInventorySize(){
    return inventorySize;
}
