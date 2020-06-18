//
// Created by agustin on 14/6/20.
//

#include "Stats.h"
#include <ctime>
#include "../Config/Calculator.h"
#include "../Config/Configuration.h"
#include <algorithm>

using namespace Config;

Stats::Stats(Race _race, Class _class, unsigned int _level, unsigned int _experience) {
    Configuration& config = Configuration::getInstance();
    Modifiers classModifier = config.configClassModifiers(_class);
    Modifiers raceModifier = config.configRaceModifiers(_race);
    classLifeMultiplier = classModifier.lifeMultiplier;
    classManaMultiplier = classModifier.manaMultiplier;
    raceLifeMultiplier = raceModifier.lifeMultiplier;
    raceManaMultiplier = raceModifier.manaMultiplier;
    constitution = classModifier.constitution + raceModifier.constitution;
    intelligence = classModifier.intelligence + raceModifier.intelligence;
    agility = classModifier.agility + raceModifier.agility;
    strength = classModifier.strength + raceModifier.strength;
    isMeditating = false;
    generalTimer = time(nullptr);
    meditationTimer = generalTimer;
    experience = _experience;
    level = _level;
    maxLife = Calculator::calculateMaxLife(classModifier, raceModifier, level);
    maxMana = Calculator::calculateMaxMana(classModifier, raceModifier, level);
    currentLife = maxLife;
    currentMana = maxMana;
}

int Stats::getTotalDamage(int weaponDamage) {
    return Calculator::calculateDamage(strength, weaponDamage);
}

unsigned int Stats::getLevel() {
    return level;
}

void Stats::increaseExperience(unsigned int _experience) {
    experience += experience;
}

int Stats::modifyLife(int damage, unsigned int attackerLevel, unsigned int defense) {
    if (damage < 0) {
        currentLife += damage;
        if (currentLife > maxLife) currentLife = maxLife;
        return damage;
    } else {
        Configuration& config = Configuration::getInstance();
        if ((attackerLevel - level) < config.configMaxLevelDif()
            && !Calculator::canDodge(agility)) {
            int totalDamage = std::max(damage - static_cast<int>(defense), 0);
            currentLife -= totalDamage;
            return totalDamage;
        }
    }
    return 0;
}
