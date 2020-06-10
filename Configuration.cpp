//
// Created by ivan on 8/6/20.
//

#include "Configuration.h"

#define HUMAN 0
#define ELF 1
#define DWARF 2
#define GNOME 3

#define MAGE 0
#define CLERIC 1
#define PALADIN 2
#define WARRIOR 3

#define SKELETON 0
#define ZOMBIE 1
#define SPIDER 2
#define GOBLIN 3

Configuration &Configuration::getInstance() {
    static Configuration instance;
    return instance;
}

Configuration::Configuration() {
    FileReader fileReader("../config.json");

    fileReader.getClassModifiers(classModifiers);
    fileReader.getRaceModifiers(raceModifiers);
    fileReader.getMonsterStats(monsterStats);

    fileReader.getGoldModifiers(goldModifiers);
    fileReader.getXPModifiers(xpModifiers);

    criticalAttackChance = fileReader.getCritAttackChance();
    dodgeChance = fileReader.getDodgeChance();

    newbieLevel = fileReader.getNewbieLevel();
    maxLevelDif =  fileReader.getmaxLevelDif();
    playerVisionRange = fileReader.getPlayerVisionRange();
}

Modifiers Configuration::configMageModifiers(){
    return classModifiers[MAGE];
}

Modifiers Configuration::configClericModifiers(){
    return classModifiers[CLERIC];
}

Modifiers Configuration::configPaladinModifiers(){
    return classModifiers[PALADIN];
}

Modifiers Configuration::configWarriorModifiers(){
    return classModifiers[WARRIOR];
}

Modifiers Configuration::configHumanModifiers(){
    return raceModifiers[HUMAN];
}

Modifiers Configuration::configElfModifiers(){
    return raceModifiers[ELF];
}

Modifiers Configuration::configDwarfModifiers(){
    return raceModifiers[DWARF];
}

Modifiers Configuration::configGnomeModifiers(){
    return raceModifiers[GNOME];
}

MonsterStats Configuration::configSkeletonStats(){
    return monsterStats[SKELETON];
}

MonsterStats Configuration::configZombieStats(){
    return monsterStats[ZOMBIE];
}

MonsterStats Configuration::configSpiderStats(){
    return monsterStats[SPIDER];
}

MonsterStats Configuration::configGoblinStats(){
    return monsterStats[GOBLIN];
}

GoldModifiers Configuration::configGoldModifiers(){
    return goldModifiers;
}

XPModifiers Configuration::configXPModifiers(){
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
