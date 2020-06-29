//
// Created by agustin on 8/6/20.
//

#include "Player.h"
#include "../Config/Calculator.h"
#include "../AttackResult.h"
#include "../Game/Game.h"
#include "../Items/Miscellaneous/Gold.h"
#include "../Config/Configuration.h"
#include "Citizens/ProductData.h"
#include <msgpack.hpp>

using namespace GameType;

MSGPACK_ADD_ENUM(GameType::Race)
MSGPACK_ADD_ENUM(GameType::ID)

////////////////////////////////////PUBLIC///////////////////////////////

Player::Player(Game& _game, Race _race, Class _class, unsigned int _level, unsigned int _experience
                , Coordinate _initialPosition, std::string&& _nickname):
               Entity(GameType::Entity::PLAYER, _initialPosition, std::move(_nickname), true),
               stats(_race, _class, _level, _experience),
               game(_game) {
    race = _race;
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

bool Player::spendGold(int amount) {
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
    if ((!stats.isDead()) && (item)) {
        stats.stopMeditating();
        if (item->isGold()) {
            std::shared_ptr<Gold> aux = std::dynamic_pointer_cast<Gold>(item);
            gold += aux->getamount();
            return true;
        } else {
            return inventory.addItem(std::move(item));
        }
    }
    return false;
}

std::shared_ptr<Item> Player::removeItem(const std::string &itemName) {
    if (!stats.isDead()) {
        stats.stopMeditating();
        return inventory.removeItem(itemName);
    }
    return nullptr;
}

void Player::useItem(int itemPosition) {
    if (!stats.isDead()) {
        stats.stopMeditating();
        inventory.useItem(*this, itemPosition);
    }
}

const std::string &Player::getNickname() const {
    return Entity::getNickname();
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

void Player::requestMove(GameType::Direction direction) {
    Entity::requestMove(game, direction);
}

void Player::unequip(EquipmentPlace clothing) {
    if (!stats.isDead()) {
        stats.stopMeditating();
        inventory.unequip(clothing);
    }
}

void Player::unequip() {
    if (!stats.isDead()) {
        stats.stopMeditating();
        inventory.unequip();
    }
}

void Player::dropItem(unsigned int itemPosition) {
    std::shared_ptr<Item> aux = inventory.removeItem(itemPosition);
    if (aux) {
        game.dropItems(std::move(aux), currentPosition);
    }
}

void Player::buyFrom(const std::string &itemName, Coordinate npcPosition) {
    game.buy(*this, itemName, npcPosition);
}

void Player::sellTo(const std::string &itemName, Coordinate npcPosition) {
    game.sell(*this, itemName, npcPosition);
}

void Player::withdrawFrom(const std::string &itemName, Coordinate npcPosition) {
    game.withdraw(*this, itemName, npcPosition);
}

void Player::listFrom(Coordinate npcPosition) {
    std::list<ProductData> products;
    game.list(*this, products, npcPosition);

    //FALTA HACER QUE SE MANDE AL CLIENTE

}

void Player::depositTo(const std::string &itemName, Coordinate npcPosition) {
    game.deposit(*this, itemName, npcPosition);
}

void Player::operator>>(std::stringstream &buffer) {
    Entity::operator>>(buffer);
    msgpack::type::tuple<Race> data(race);
    msgpack::pack(buffer, data);
    stats.storeLifeStatus(buffer);
    inventory.storeEquippedItems(buffer);
}

void Player::storeAllRelevantData(std::stringstream& buffer) const {
    msgpack::type::tuple<GameType::ID> messageTypeData(PLAYER_DATA);
    msgpack::pack(buffer, messageTypeData);
    msgpack::type::tuple<int32_t> data(gold);
    msgpack::pack(buffer, data);
    inventory.storeAllData(buffer);
    stats.storeAllRelevantData(buffer);
    msgpack::type::tuple<int32_t, int32_t> position(currentPosition.iPosition,
                                                currentPosition.jPosition);
    msgpack::pack(buffer, position);
}
