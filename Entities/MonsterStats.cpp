//
// Created by marcos on 20/6/20.
//

#include "MonsterStats.h"
#include "../Config/Configuration.h"
#include "../Config/Calculator.h"
#include "../AttackResult.h"

MonsterStats::MonsterStats(GameType::Monster type) {
    Configuration& config = Configuration::getInstance();
    Config::MonsterStats stats = config.configMonsterStats(type);
    level = Calculator::getRandomInt(static_cast<int>(stats.minLevel),
                                     static_cast<int>(stats.maxLevel));
    constitution = stats.constitution + level;
    strength = stats.strength + level;
    agility = stats.agility + level;
    damage = static_cast<int>(stats.damage);
    rangeOfVision = stats.rangeOfVision;
    maxLife = stats.life;
    currentLife = maxLife;
    speed = stats.speed;
}

bool MonsterStats::_isDead() const {
    return currentLife == 0;
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

AttackResult MonsterStats::modifyLife(int _damage, unsigned int attackerLevel) {
    currentLife -= _damage;
    if (currentLife < 0) {
        currentLife = 0;
    }
    unsigned int experience = Calculator::calculateAttackXP(damage,
                                                            attackerLevel, level);
    if (_isDead() && damage > 0) {
        experience += Calculator::calculateKillXP(attackerLevel, level, maxLife);
    }
    return {_damage, experience};
}

int MonsterStats::getCurrentLife() const {
    return currentLife;
}

unsigned int MonsterStats::getMaxLife() const {
    return maxLife;
}
