//
// Created by agustin on 8/6/20.
//

#include "Player.h"
#include "../Config/Calculator.h"

using namespace Config;

////////////////////////////////////PUBLIC///////////////////////////////

Player::Player(Game& _game, Race _race, Class _class, unsigned int _level, unsigned int _experience
                , Coordinate _initialPosition, const std::string& _nickname):
               Entity(_initialPosition), stats(_race, _class, _level, _experience),
               game(_game){
    nickname = _nickname;
    gold = 0; //todo habria que recibir la cantidad de oro tambien,
                //todo o pasar por referencia la clase que maneje el archivo de
                //todo persistencia directamente
}

void Player::move(Direction direction) {
    switch (direction) {
        case DIRECTION_UP:
            --currentPosition.jPosition;
            break;
        case DIRECTION_DOWN:
            ++currentPosition.jPosition;
            break;
        case DIRECTION_LEFT:
            ++currentPosition.iPosition;
            break;
        case DIRECTION_RIGHT:
            --currentPosition.iPosition;
            break;
    }
}

void Player::attack(Coordinate target) {
    if (!stats.isDead()) {
        int weaponDamage;
        weaponDamage = inventory.getWeaponDamage(currentPosition, target);
        int totalDamage = stats.getTotalDamage(weaponDamage);
        AttackResult result = game.attackPosition(totalDamage, stats.getLevel(), target);
        stats.increaseExperience(result.experience);
        //todo ver el tema de guardar el danio ocasionado
    }
}

void Player::_dropItems() {
    if (!stats.isDead()) {
        std::list<std::shared_ptr<Item>> items = inventory.dropAllItems();
        game.dropItems(std::move(items), currentPosition);
    }
}

AttackResult Player::attacked(int damage, unsigned int attackerLevel) {
    if (!stats.isDead()) {
        unsigned int defense = inventory.getDefense();
        int totalDamage = stats.modifyLife(damage, attackerLevel, defense);
        unsigned int experience = Calculator::calculateAttackXP(totalDamage,
                                                                attackerLevel, stats.getLevel());
        if (stats.getCurrentLife() == 0 && totalDamage > 0) {
            _dropItems();
            experience += Calculator::calculateKillXP(attackerLevel,
                                                      stats.getLevel(), stats.getMaxLife());
        }
        return {totalDamage, experience};
    }
    return {0, 0};
}

bool Player::isMonsterTarget() {
    return !stats.isDead();
}

bool Player::spendGold(unsigned int amount) {
    if ((!stats.isDead()) && (amount <= gold)) {
        gold -= amount;
        return true;
    }
    return false;
}

void Player::receiveGold(unsigned int amount) {
    if (!stats.isDead()) {
        gold += amount;
    }
}

bool Player::storeItem(std::shared_ptr<Item> &&item) {
    if (!stats.isDead()) {
        return inventory.addItem(std::move(item));
    }
    return false;
}

std::shared_ptr<Item> Player::removeItem(const std::string &itemName) {
    if (!stats.isDead()) {
        return inventory.removeItem(itemName);
    }
    std::shared_ptr<Item> aux;
    return aux;
}

void Player::useItem(int itemPosition) {
    if (!stats.isDead()) {
        inventory.useItem(*this, itemPosition);
    }
}

const std::string &Player::getNickname() const {
    return nickname;
}

void Player::restoreLife(unsigned int ammount) {
    if (!stats.isDead()) {
        stats.restoreLife(ammount);
    }
}

void Player::restoreMana(unsigned int ammount) {
    if (!stats.isDead()) {
        stats.restoreMana(ammount);
    }
}
