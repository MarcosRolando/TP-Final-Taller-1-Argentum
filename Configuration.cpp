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

    criticalAttackChance = fileReader.getCritAttackChance();
    dodgeChance = fileReader.getDodgeChance();

    newbieLevel = fileReader.getNewbieLevel();
    maxLevelDif =  fileReader.getmaxLevelDif();

    inventorySize = fileReader.getInventorySize();
}

unsigned int Configuration::getMageHealth() const {
    return mageModifiers.health;
}
unsigned int Configuration::getMageMana() const {
    return mageModifiers.mana;
}
unsigned int Configuration::getMageConstitution() const {
    return mageModifiers.constitution;
}
unsigned int Configuration::getMageAgility() const {
    return mageModifiers.agility;
}
unsigned int Configuration::getMageIntelligence() const {
    return mageModifiers.intelligence;
}
unsigned int Configuration::getMageMeditationRate() const {
    return mageModifiers.meditationRate;
}

