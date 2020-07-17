//
// Created by agustin on 14/6/20.
//

#include "PlayerStats.h"
#include "../Config/Calculator.h"
#include "../Config/Configuration.h"
#include "Minichat.h"
#include <algorithm>
#include <msgpack.hpp>

#define MUCH_LEVEL_DIFF_MESSAGE "I think the level gap between us is a tad much, I'm level "
#define CRITICAL_MESSAGE "That must have hurt! Critical! "
#define DODGE_MESSAGE "Too weak, too slow. "
#define STARTED_MEDITATING_MESSAGE "Started meditating\n"
#define STOPPED_MEDITATING_MESSAGE "Stopped meditating\n"

const double TIME_FOR_RECOVERY = 3000.0; //3 seconds (timeStep is in miliseconds) //todo poder modificarlo desde el archivo

using namespace GameType;

PlayerStats::PlayerStats(const PlayerData& data) {
    Configuration& config = Configuration::getInstance();
    Config::Modifiers classModifier = config.configClassModifiers(data.pClass);
    Config::Modifiers raceModifier = config.configRaceModifiers(data.pRace);
    classLifeMultiplier = classModifier.lifeMultiplier;
    classManaMultiplier = classModifier.manaMultiplier;
    raceLifeMultiplier = raceModifier.lifeMultiplier;
    raceManaMultiplier = raceModifier.manaMultiplier;
    _loadInitialStats(classModifier, raceModifier, data);
    _loadGenericStats(classModifier, raceModifier, data);
}

void PlayerStats::_loadGenericStats(Config::Modifiers& classM, Config::Modifiers& raceM,
                                    const PlayerData& data) {
    isMeditating = false;
    timeElapsedLife = 0;
    timeElapsedMana = 0;
    experience = data.experience;
    level = data.level;
    maxLife = Calculator::calculateMaxLife(constitution, classLifeMultiplier, raceLifeMultiplier, level);
    maxMana = Calculator::calculateMaxMana(intelligence, classManaMultiplier, raceManaMultiplier, level);
    currentLife = maxLife;
    currentMana = maxMana;
    nextLevelExperience = Calculator::calculateNextLevelXP(level);
    recoveryRate = raceM.recoveryRate;
    meditationRate = classM.meditationRate;
}

void PlayerStats::_loadInitialStats(Config::Modifiers& classM, Config::Modifiers& raceM,
                                    const PlayerData& data) {
    if (data.isNewPlayer) {
        constitution += classM.constitution + raceM.constitution;
        intelligence += classM.intelligence + raceM.intelligence;
        agility += classM.agility + raceM.agility;
        strength += classM.strength + raceM.strength;
    } else {
        constitution = data.constitution;
        intelligence = data.intelligence;
        agility = data.agility;
        strength = data.strength;
    }
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
    currentLife = maxLife;
    currentMana = maxMana;
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

std::pair<int, bool> PlayerStats::modifyLife(int damage, unsigned int attackerLevel, unsigned int defense,
                            bool isAPlayer, std::string& attackedMessage) {
    if (damage < 0) {
        currentLife += damage;
        if (currentLife > maxLife) currentLife = maxLife;
        currentMana = 0;
        return {damage, false};
    } else {
        Configuration& config = Configuration::getInstance();
        if (isAPlayer && std::abs(static_cast<int32_t>(attackerLevel) - level) >
                                    static_cast<int32_t>(config.configMaxLevelDif())) {
            attackedMessage += MUCH_LEVEL_DIFF_MESSAGE + std::to_string(level) + "\n";
            return {0, false};
        }
        if (Calculator::isCritical()) {
            attackedMessage += CRITICAL_MESSAGE;
            damage = damage * 2;
        } else if (Calculator::canDodge(agility)) {
            attackedMessage += DODGE_MESSAGE;
            return {0, true};
        }
        int totalDamage = std::max(damage - static_cast<int>(defense), 0);
        currentLife -= totalDamage;
        if (currentLife <= 0) {
            currentLife = 0;
            currentMana = 0;
        }
        if (totalDamage > 0) {
            timeElapsedLife = 0.0;
        }
        return {totalDamage, false};
    }
}

int PlayerStats::getMaxLife() const {
    return maxLife;
}

int PlayerStats::getCurrentLife() const {
    return currentLife;
}

void PlayerStats::restoreLife(unsigned int amount) {
    currentLife += static_cast<int>(amount);
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
    return (getCurrentLife() == 0);
}

void PlayerStats::update(double timeStep) {
    if (isDead()) {
        return;
    }
    timeElapsedLife += timeStep;
    timeElapsedMana += timeStep;
    if (timeElapsedLife >= TIME_FOR_RECOVERY) {
        currentLife += Calculator::lifeRecovered(recoveryRate, timeElapsedLife/1000);
        if (currentLife > maxLife) {
            currentLife = maxLife;
        }
        timeElapsedLife = 0.0;
    }
    if (timeElapsedMana >= TIME_FOR_RECOVERY) {
        if (isMeditating) {
            currentMana += Calculator::manaRecoveredWithMeditation(meditationRate,
                                                                   intelligence, timeElapsedMana/1000);
        } else {
            currentMana += Calculator::manaRecoveredNoMeditation(recoveryRate,
                                                                 timeElapsedMana/1000);
        }
        if (currentMana >= maxMana) {
            currentMana = maxMana;
        }
        timeElapsedMana = 0.0;
    }
}

void PlayerStats::startMeditating(Minichat& minichat) {
    if (!isMeditating) {
        isMeditating = true;
        minichat.addMessage(STARTED_MEDITATING_MESSAGE);
    }
}

void PlayerStats::stopMeditating(Minichat& minichat) {
    if (isMeditating) {
        isMeditating = false;
        minichat.addMessage(STOPPED_MEDITATING_MESSAGE);
    }
}

int32_t& PlayerStats::getCurrentMana() {
    return currentMana;
}

void PlayerStats::restore() {
    currentMana = maxMana;
    currentLife = maxLife;
}

void PlayerStats::storeAllRelevantData(std::stringstream& buffer) const {
    msgpack::type::tuple<int32_t, int32_t, int32_t> xpData(experience, nextLevelExperience, level);
    msgpack::pack(buffer, xpData);
    msgpack::type::tuple<int32_t, int32_t> manaData(currentMana, maxMana);
    msgpack::pack(buffer, manaData);
    msgpack::type::tuple<int32_t, int32_t> lifeData(currentLife, maxLife);
    msgpack::pack(buffer, lifeData);
    msgpack::type::tuple<int32_t, int32_t, int32_t, int32_t> statsData(strength,
                            constitution, intelligence, agility);
    msgpack::pack(buffer, statsData);
}

void PlayerStats::storeLifeStatus(std::stringstream& buffer) const {
    msgpack::type::tuple<bool> isAlive(!isDead());
    msgpack::pack(buffer, isAlive);
}

void PlayerStats::getData(PlayerData &pData) const {
    pData.level = level;
    pData.experience = experience;
    pData.constitution = constitution;
    pData.strength = strength;
    pData.agility = agility;
    pData.intelligence = intelligence;
}

bool PlayerStats::consumeMana(unsigned int amount) {
    if (currentMana < static_cast<int>(amount)) {
        return false;
    }
    if (amount != 0) {
        currentMana -= amount;
        timeElapsedMana = 0;
    }
    return true;
}

