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
    nextLevelExperience = Calculator::calculateNextLevelXP(level);
}

int Stats::getTotalDamage(int weaponDamage) const {
    return Calculator::calculateDamage(strength, weaponDamage);
}

unsigned int Stats::getLevel() const {
    return level;
}

void Stats::_increaseStats() {
    ++strength;
    ++agility;
    ++intelligence;
    ++constitution;
}

void Stats::increaseExperience(unsigned int _experience) {
    experience += _experience;
    if (experience >= nextLevelExperience) {
        ++level;
        _increaseStats();
        experience = 0;
        nextLevelExperience = Calculator::calculateNextLevelXP(level);
    }

}

int Stats::modifyLife(int damage, unsigned int attackerLevel, unsigned int defense) {
    if (currentLife == 0) return 0;
    if (damage < 0) {
        currentLife += damage;
        if (currentLife > maxLife) currentLife = maxLife;
        return damage;
    } else {
        Configuration& config = Configuration::getInstance();
        if (std::abs(static_cast<int>(attackerLevel - level)) < config.configMaxLevelDif()
            && !Calculator::canDodge(agility)) {
            int totalDamage = std::max(damage - static_cast<int>(defense), 0);
            currentLife -= totalDamage;
            if (currentLife < 0) currentLife = 0;
            return totalDamage;
        }
    }
    return 0;
}

int Stats::getMaxLife() const {
    return maxLife;
}

int Stats::getCurrentLife() const {
    return currentLife;
}

void Stats::restoreLife(unsigned int ammount) {
    currentLife += ammount;
    if (currentLife > maxLife) {
        currentLife = maxLife;
    }
}

void Stats::restoreMana(unsigned int ammount) {
    currentMana += ammount;
    if (currentMana > maxMana) {
        currentMana = maxMana;
    }
}

bool Stats::isDead() {
    return getCurrentLife() == 0;
}
