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
    playerVisionRange = fileReader.getPlayerVisionRange();
}

Modifiers Configuration::configMageModifiers(){
    return mageModifiers;
}

Modifiers Configuration::configClericModifiers(){
    return clericModifiers;
}

Modifiers Configuration::configPaladinModifiers(){
    return paladinModifiers;
}

Modifiers Configuration::configWarriorModifiers(){
    return warriorModifiers;
}

Modifiers Configuration::configHumanModifiers(){
    return humanModifiers;
}

Modifiers Configuration::configElfModifiers(){
    return elfModifiers;
}

Modifiers Configuration::configDwarfModifiers(){
    return dwarfModifiers;
}

Modifiers Configuration::configGnomeModifiers(){
    return gnomeModifiers;
}

MonsterStats Configuration::configSkeletonStats(){
    return skeletonStats;
}

MonsterStats Configuration::configSpiderStats(){
    return spiderStats;
}

MonsterStats Configuration::configZombieStats(){
    return zombieStats;
}

MonsterStats Configuration::configGoblinStats(){
    return goblinStats;
}

GoldModifiers Configuration::configGoldModifiers(){
    return goldModifiers;
}

XPModifiers Configuration::configXPModifiers(){
    return xpModifiers;
}

float Configuration::configCriticalAttackChance(){
    return criticalAttackChance;
}

float Configuration::configDodgeChance(){
    return dodgeChance;
}

unsigned int Configuration::configNewbieLevel(){
    return newbieLevel;
}

unsigned int Configuration::configMaxLevelDif(){
    return maxLevelDif;
}

unsigned int Configuration::configPlayerVisionRange() {
    return playerVisionRange;
}
