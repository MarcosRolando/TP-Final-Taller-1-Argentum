//
// Created by marcos on 20/6/20.
//

#include "MonsterStats.h"
#include "../Config/Configuration.h"
#include "../Config/Calculator.h"
#include "AttackResult.h"

#define DODGE_MESSAGE "Monster dodged! "

MonsterStats::MonsterStats(GameType::Entity type) {
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

/*
AttackResult MonsterStats::modifyLife(int _damage, unsigned int attackerLevel) {
    AttackResult result {0, 0, ""};
    if (Calculator::canDodge(getAgility())) {
        result.resultMessage += DODGE_MESSAGE;
        return result;
    }
    currentLife -= _damage;
    if (currentLife < 0) {
        currentLife = 0;
    }
    unsigned int experience = Calculator::calculateAttackXP(_damage,
                                                            attackerLevel, level);
    if (_isDead() && _damage > 0) {
        experience += Calculator::calculateKillXP(attackerLevel, level, maxLife);
    }
    result.damage = _damage;
    result.experience = experience;
    return result;
}
*/


std::pair<int, bool> MonsterStats::modifyLife(int _damage) {
    //AttackResult result {0, 0, ""};
    if (Calculator::canDodge(getAgility())) {
        //result.resultMessage += DODGE_MESSAGE;
        return {0, true};
    }
    currentLife -= _damage;
    if (currentLife < 0) {
        currentLife = 0;
    }
    return {_damage, false};
    //unsigned int experience = Calculator::calculateAttackXP(_damage, attackerLevel, level);
    /*
    if (_isDead() && _damage > 0) {
        experience += Calculator::calculateKillXP(attackerLevel, level, maxLife);
    }
    */
    //result.damage = _damage;
    //result.experience = experience;
    //return result;
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
