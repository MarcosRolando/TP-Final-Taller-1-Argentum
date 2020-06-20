//
// Created by agustin on 14/6/20.
//

#include "PlayerStats.h"
#include <ctime>
#include "../Config/Calculator.h"
#include <algorithm>

using namespace GameType;

PlayerStats::PlayerStats(Race _race, Class _class, unsigned int _level, unsigned int _experience) {
    Configuration& config = Configuration::getInstance();
    Config::Modifiers classModifier = config.configClassModifiers(_class);
    Config::Modifiers raceModifier = config.configRaceModifiers(_race);
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
    maxLife = Calculator::calculateMaxLife(constitution, classLifeMultiplier, raceLifeMultiplier, level);
    maxMana = Calculator::calculateMaxMana(intelligence, classManaMultiplier, raceManaMultiplier, level);
    currentLife = maxLife;
    currentMana = maxMana;
    nextLevelExperience = Calculator::calculateNextLevelXP(level);
}

int PlayerStats::getTotalDamage(int weaponDamage) const {
    return Calculator::calculateDamage(strength, weaponDamage);
}

unsigned int PlayerStats::getLevel() const {
    return level;
}

void PlayerStats::_increaseStats() {
    ++strength;
    ++agility;
    ++intelligence;
    ++constitution;
    maxLife = Calculator::calculateMaxLife(constitution, classLifeMultiplier, raceLifeMultiplier,
                                            level);
    maxMana = Calculator::calculateMaxMana(intelligence, classManaMultiplier, raceManaMultiplier,
                                            level);
}

void PlayerStats::increaseExperience(unsigned int _experience) {
    experience += _experience;
    if (experience >= nextLevelExperience) {
        ++level;
        _increaseStats();
        experience = 0;
        nextLevelExperience = Calculator::calculateNextLevelXP(level);
    }
}

int PlayerStats::modifyLife(int damage, unsigned int attackerLevel, unsigned int defense) {
    if (currentLife == 0) return 0;
    if (damage < 0) {
        currentLife += damage;
        if (currentLife > maxLife) currentLife = maxLife;
        return damage;
    } else {
        Configuration& config = Configuration::getInstance();
        if (std::abs(static_cast<int>(attackerLevel - level)) < config.configMaxLevelDif()) {
            if (Calculator::isCritical()) {
                damage = damage * 2;
            } else if (Calculator::canDodge(agility)) {
                return 0;
            }
            int totalDamage = std::max(damage - static_cast<int>(defense), 0);
            currentLife -= totalDamage;
            if (currentLife < 0) currentLife = 0;
            return totalDamage;
        }
    }
    return 0;
}

int PlayerStats::getMaxLife() const {
    return maxLife;
}

int PlayerStats::getCurrentLife() const {
    return currentLife;
}

void PlayerStats::restoreLife(unsigned int amount) {
    currentLife += amount;
    if (currentLife > maxLife) {
        currentLife = maxLife;
    }
}

void PlayerStats::restoreMana(unsigned int amount) {
    currentMana += amount;
    if (currentMana > maxMana) {
        currentMana = maxMana;
    }
}

bool PlayerStats::isDead() const {
    return getCurrentLife() == 0;
}
