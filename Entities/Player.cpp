//
// Created by agustin on 8/6/20.
//

#include "Player.h"
#include "../Config/Calculator.h"
#include "../AttackResult.h"
#include "../Game.h"
#include "../Items/Miscellaneous/Gold.h"
#include "../Config/Configuration.h"

using namespace GameType;

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

void Player::attack(Coordinate target) {
    if (!stats.isDead()) {
        stats.stopMeditating();
        int weaponDamage;
        weaponDamage = inventory.getWeaponDamage(currentPosition, target,
                                                    stats.getCurrentMana());
        int totalDamage = stats.getTotalDamage(weaponDamage);
        AttackResult result = game.attackPosition(totalDamage, stats.getLevel(),
                                                true, target);
        stats.increaseExperience(result.experience);
        //todo ver el tema de guardar el danio ocasionado
    }
}

void Player::_dropItems() {
    if (!stats.isDead()) {
        std::list<std::shared_ptr<Item>> items = inventory.dropAllItems();
        int goldDropped = static_cast<int>(gold -
                        Calculator::calculateMaxSafeGold(stats.getLevel()));
        goldDropped = std::max(goldDropped, 0);
        gold -= goldDropped;
        if (goldDropped > 0) {
            items.emplace_back(new Gold(goldDropped));
        }
        game.dropItems(std::move(items), currentPosition);
    }
}

AttackResult Player::attacked(int damage, unsigned int attackerLevel, bool isAPlayer) {
    stats.stopMeditating();
    unsigned int newbieLevel = Configuration::getInstance().configNewbieLevel();
    if (isAPlayer && ( stats.getLevel() <= newbieLevel || attackerLevel <= newbieLevel) ) {
        return {0, 0};
    }
    if (!stats.isDead()) {
        unsigned int defense = inventory.getDefense();
        int totalDamage = stats.modifyLife(damage, attackerLevel, defense, isAPlayer);
        unsigned int experience = Calculator::calculateAttackXP(totalDamage,
                                    attackerLevel, stats.getLevel());
        if (stats.isDead() && totalDamage > 0) {
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
    stats.stopMeditating();
    if ((!stats.isDead()) && (amount <= gold)) {
        gold -= amount;
        return true;
    }
    return false;
}

void Player::receiveGold(unsigned int amount) {
    unsigned int maxGold = Calculator::calculateMaxSafeGold(stats.getLevel());
    maxGold += maxGold / 2;
    if (!stats.isDead() && (gold + amount) <= maxGold) {
        gold += amount;
    }
}

bool Player::storeItem(std::shared_ptr<Item> &&item) {
    if (!stats.isDead()) {
        stats.stopMeditating();
        return inventory.addItem(std::move(item));
    }
    return false;
}

std::shared_ptr<Item> Player::removeItem(const std::string &itemName) {
    if (!stats.isDead()) {
        stats.stopMeditating();
        return inventory.removeItem(itemName);
    }
    std::shared_ptr<Item> aux;
    return aux;
}

void Player::useItem(int itemPosition) {
    if (!stats.isDead()) {
        stats.stopMeditating();
        inventory.useItem(*this, itemPosition);
    }
}

const std::string &Player::getNickname() const {
    return nickname;
}

void Player::restoreLife(unsigned int amount) {
    if (!stats.isDead()) {
        stats.restoreLife(amount);
    }
}

void Player::restoreMana(unsigned int amount) {
    if (!stats.isDead()) {
        stats.restoreMana(amount);
    }
}

void Player::meditate() {
    if (!stats.isDead()) {
        stats.startMeditating();
    }
}

void Player::update(double timeStep) {
    Entity::update(timeStep); /*actualiza movimiento*/
    stats.update(timeStep); /*actualiza la vida y manda en base al tiempo/meditacion*/
}

void Player::move(Direction direction) {
    Entity::move(game, direction);
}

void Player::unequip(EquipmentPlace clothing) {
    if (!stats.isDead()) {
        stats.startMeditating();
        inventory.unequip(clothing);
    }
}

void Player::unequip() {
    if (!stats.isDead()) {
        stats.startMeditating();
        inventory.unequip();
    }
}
