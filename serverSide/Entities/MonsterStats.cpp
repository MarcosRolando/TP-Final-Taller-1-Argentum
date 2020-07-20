//
// Created by marcos on 20/6/20.
//

#include "MonsterStats.h"
#include "../Config/Configuration.h"
#include "../Config/Calculator.h"

MonsterStats::MonsterStats(GameType::Entity type) {
    Configuration& config = Configuration::getInstance();
    Config::MonsterStats stats = config.configMonsterStats(type);
    level = Calculator::getRandomInt(static_cast<int>(stats.minLevel),
                                     static_cast<int>(stats.maxLevel));
    constitution = stats.constitution + level;
    strength = stats.strength + level;
    agility = stats.agility + level;
    damage = static_cast<int>(stats.damage) + 10 * strength;
    rangeOfVision = stats.rangeOfVision;
    maxLife = stats.life + constitution * 10;
    currentLife = maxLife;
    speed = stats.speed;
}

unsigned int MonsterStats::getRangeOfVision() const {
    return rangeOfVision;
}

int MonsterStats::getDamage() const {
    return damage;
}

unsigned int MonsterStats::getLevel() const {
    return level;
}

std::pair<int, bool> MonsterStats::modifyLife(int _damage) {
    if (Calculator::canDodge(getAgility())) {
        return {0, true};
    }
    currentLife -= _damage;
    if (currentLife < 0) {
        currentLife = 0;
    }
    return {_damage, false};
}

int MonsterStats::getCurrentLife() const {
    return currentLife;
}

int MonsterStats::getMaxLife() const {
    return maxLife;
}

unsigned int MonsterStats::getAgility() const {
    return agility;
}
