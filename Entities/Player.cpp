//
// Created by agustin on 8/6/20.
//

#include "Player.h"
#include "../Config/Calculator.h"
#include "../AttackResult.h"
#include "../Game/Game.h"
#include "../Items/Miscellaneous/Gold.h"
#include "../Config/Configuration.h"
#include <msgpack.hpp>

#define ATTACKER_IS_NEWBIE_MESSAGE "I won't lose my time on a low level newbie like you!\n "
#define PLAYER_IS_A_NEWBIE_MESSAGE "Surely you have better things to do than attack a low level newbie like me...\n"
#define PLAYER_IS_DEAD_MESSAGE "You can't kill a ghost, you know?\n"

using namespace GameType;

MSGPACK_ADD_ENUM(GameType::Race)
MSGPACK_ADD_ENUM(GameType::EventID)

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

int32_t Player::attack(Coordinate target) {
    if (!stats.isDead()) {
        stats.stopMeditating();
        int weaponDamage;
        weaponDamage = inventory.getWeaponDamage(currentPosition, target,
                                                    stats.getCurrentMana());
        int totalDamage = stats.getTotalDamage(weaponDamage);
        AttackResult result = game.attackPosition(totalDamage, stats.getLevel(),
                                                true, target);
        stats.increaseExperience(result.experience);
        chat.addMessage(std::move(result.resultMessage));
        return inventory.getWeaponId();
    }
    return -1;
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
    if (isAPlayer) {
        if (stats.getLevel() <= newbieLevel) {
            return {0, 0, PLAYER_IS_A_NEWBIE_MESSAGE};
        } else if (attackerLevel <= newbieLevel) {
            return {0, 0, ATTACKER_IS_NEWBIE_MESSAGE};
        }
    }
    if (!stats.isDead()) {
        std::string attackedMessage;
        unsigned int defense = inventory.getDefense();
        int totalDamage = stats.modifyLife(damage, attackerLevel, defense, isAPlayer, attackedMessage);
        unsigned int experience = Calculator::calculateAttackXP(totalDamage,
                                    attackerLevel, stats.getLevel());
        if (stats.isDead() && totalDamage > 0) {
            _dropItems();
            experience += Calculator::calculateKillXP(attackerLevel,
                    stats.getLevel(), stats.getMaxLife());
        }
        attackedMessage += "You damaged " + getNickname() + " by " + std::to_string(totalDamage);
        attackedMessage += " (Remaining Life: " + std::to_string(stats.getCurrentLife()) +
                            " , XP Gained: " + std::to_string(experience) + "\n";
        return {totalDamage, experience, std::move(attackedMessage)};
    } else {
        return {0, 0, PLAYER_IS_DEAD_MESSAGE};
    }
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

UseReturnData Player::useItem(int itemPosition) {
    if (!stats.isDead()) {
        stats.stopMeditating();
        return inventory.useItem(*this, itemPosition);
    }
    return {GameType::EQUIPMENT_PLACE_NONE, -1};
}

/*
const std::string &Player::getNickname() const {
    return Entity::getNickname();
}
*/

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
    Entity::update(timeStep, game); /*actualiza movimiento*/
    stats.update(timeStep); /*actualiza la vida y manda en base al tiempo/meditacion*/
}

bool Player::unequip(EquipmentPlace clothing) {
    if (!stats.isDead()) {
        stats.stopMeditating();
        return inventory.unequip(clothing);
    }
    return false;
}

bool Player::unequip() {
    if (!stats.isDead()) {
        stats.stopMeditating();
        return inventory.unequip();
    }
    return false;
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

/*
void Player::listFrom(Coordinate npcPosition) {
    std::list<ProductData> products;
    game.list(*this, products, npcPosition);

    //FALTA HACER QUE SE MANDE AL CLIENTE

}
*/


void Player::listFrom(Coordinate npcPosition, std::stringstream &data) {
    game.list(*this, npcPosition, data);
}

void Player::depositTo(const std::string &itemName, Coordinate npcPosition) {
    game.deposit(*this, itemName, npcPosition);
}

void Player::operator>>(std::stringstream &buffer) const {
    Entity::operator>>(buffer);
    msgpack::type::tuple<Race> data(race);
    msgpack::pack(buffer, data);
    stats.storeLifeStatus(buffer);
    inventory.storeEquippedItems(buffer);
}

void Player::storeAllRelevantData(std::stringstream& buffer) const {
    msgpack::type::tuple<int32_t> data(gold);
    msgpack::pack(buffer, data);
    inventory.storeAllData(buffer);
    stats.storeAllRelevantData(buffer);
    msgpack::type::tuple<int32_t, int32_t> position(currentPosition.iPosition,
                                                currentPosition.jPosition);
    msgpack::pack(buffer, position);
    msgpack::type::tuple<std::string> minichat(chat.getMessages());
    msgpack::pack(buffer, minichat);
}

void Player::clearMinichat() {
    chat.clear();
}
