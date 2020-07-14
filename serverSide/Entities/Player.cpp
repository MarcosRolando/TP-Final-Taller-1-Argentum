//
// Created by agustin on 8/6/20.
//

#include "Player.h"
#include "../Config/Calculator.h"
#include "AttackResult.h"
#include "../Game/Game.h"
#include "../Items/Miscellaneous/Gold.h"
#include "../Config/Configuration.h"
#include "../Game/Events/Drop.h"
#include "../Game/Events/NotifyDeath.h"
#include <msgpack.hpp>

#define ATTACKER_IS_NEWBIE_MESSAGE "I won't lose my time on a low level newbie like you!\n"
#define PLAYER_IS_A_NEWBIE_MESSAGE "Surely you have better things to do than attack a low level newbie like me...\n"
#define PLAYER_IS_DEAD_MESSAGE "You can't kill a ghost, you know?\n"

using namespace GameType;

MSGPACK_ADD_ENUM(GameType::Race)
MSGPACK_ADD_ENUM(GameType::EventID)

////////////////////////////////////PUBLIC///////////////////////////////

Player::Player(Game& _game, Coordinate _initialPosition, PlayerData& data):
               Entity(GameType::Entity::PLAYER, _initialPosition, std::move(data.nickname),
                                                                                true),
               inventory(data),
               stats(data),
               game(_game) {

    speed = Configuration::getInstance().configPlayerSpeed();
    pClass = data.pClass;
    race = data.pRace;
    gold = data.gold;
}

int32_t Player::attack(Coordinate target) {
    int32_t returnValue = -1;
    if (!stats.isDead()) {
        stats.stopMeditating(chat);
        int weaponDamage;
        weaponDamage = inventory.getWeaponDamage(currentPosition, target, stats);
        int totalDamage = stats.getTotalDamage(weaponDamage);
        if (totalDamage != 0) {
            std::pair<AttackResult, bool> result = game.attackPosition(totalDamage, stats.getLevel(),
                                                      true, target);
            stats.increaseExperience(result.first.experience);
            chat.addMessage(std::move(result.first.resultMessage));
            if (result.second) {
                returnValue = inventory.getWeaponId();
            }
        }
    }
    return returnValue;
}

void Player::_dropItems() {
    std::list<std::shared_ptr<Item>> items = inventory.dropAllItems();
    int goldDropped = static_cast<int>(gold -
                                       Calculator::calculateMaxSafeGold(stats.getLevel()));
    goldDropped = std::max(goldDropped, 0);
    gold -= goldDropped;
    if (goldDropped > 0) {
        items.emplace_back(std::make_shared<Gold>(goldDropped));
    }
    if (!items.empty()) {
        //game.dropItems(std::move(items), currentPosition);
        game.pushEvent(std::unique_ptr<Event>(new Drop(game, std::move(items), currentPosition)));
    }
}

AttackResult Player::attacked(int damage, unsigned int attackerLevel, bool isAPlayer) {
    stats.stopMeditating(chat);
    unsigned int newbieLevel = Configuration::getInstance().configNewbieLevel();
    if (!stats.isDead()) {
        if (isAPlayer) {
            if (stats.getLevel() <= newbieLevel) {
                return {0, 0, PLAYER_IS_A_NEWBIE_MESSAGE};
            } else if (attackerLevel <= newbieLevel) {
                return {0, 0, ATTACKER_IS_NEWBIE_MESSAGE};
            }
        }
        std::string attackedMessage;
        unsigned int defense = inventory.getDefense();
        int totalDamage = stats.modifyLife(damage, attackerLevel, defense, isAPlayer, attackedMessage);
        unsigned int experience = Calculator::calculateAttackXP(totalDamage,
                                    attackerLevel, stats.getLevel());
        if (stats.isDead() && totalDamage > 0) {
            _dropItems();
            experience += Calculator::calculateKillXP(attackerLevel,
                    stats.getLevel(), stats.getMaxLife());
            game.pushEvent(std::unique_ptr<Event>(new NotifyDeath(*this)));
        }
        std::string damageString = std::to_string(totalDamage);
        attackedMessage += "You damaged " + getNickname() + " by " + damageString;
        attackedMessage += " (Remaining Life: " + std::to_string(stats.getCurrentLife()) +
                            " , XP Gained: " + std::to_string(experience) + ")\n";
        if (totalDamage >= 0) {
            chat.addMessage("You lost " + damageString + " health points\n");
        } else if (totalDamage < 0) {
            chat.addMessage("You healed " + damageString + " health points\n");
        }
        return {totalDamage, experience, std::move(attackedMessage)};
    } else {
        return {0, 0, PLAYER_IS_DEAD_MESSAGE};
    }
}

bool Player::isMonsterTarget() {
    return !stats.isDead();
}

bool Player::spendGold(int amount) {
    stats.stopMeditating(chat);
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

bool Player::storeItem(std::shared_ptr<Item> &item) {
    if ((!stats.isDead()) && (item)) {
        stats.stopMeditating(chat);
        if (item->isGold()) {
            std::shared_ptr<Gold> aux = std::dynamic_pointer_cast<Gold>(item);
            gold += aux->getAmount();
            return true;
        } else {
            return inventory.addItem(item);
        }
    }
    return false;
}

std::shared_ptr<Item> Player::removeItem(const std::string &itemName) {
    if (!stats.isDead()) {
        stats.stopMeditating(chat);
        return inventory.removeItem(itemName);
    }
    return nullptr;
}

UseReturnData Player::useItem(int itemPosition) {
    if (!stats.isDead()) {
        stats.stopMeditating(chat);
        return inventory.useItem(*this, itemPosition);
    }
    return {GameType::EQUIPMENT_PLACE_NONE, -1};
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
        stats.startMeditating(chat);
    }
}

void Player::update(double timeStep) {
    Entity::update(timeStep, game); /*actualiza movimiento*/
    stats.update(timeStep); /*actualiza la vida y manda en base al tiempo/meditacion*/
}

bool Player::unequip(EquipmentPlace clothing) {
    if (!stats.isDead()) {
        stats.stopMeditating(chat);
        return inventory.unequip(clothing);
    }
    return false;
}

bool Player::unequip() {
    if (!stats.isDead()) {
        stats.stopMeditating(chat);
        return inventory.unequip();
    }
    return false;
}

//ItemData Player::dropItem(unsigned int itemPosition) {
const Item* Player::dropItem(unsigned int itemPosition) {
    std::shared_ptr<Item> aux = inventory.removeItem(itemPosition);
    //ItemData returnData = {GameType::ITEM_TYPE_NONE, -1, currentPosition};
    const Item* returnData = aux.get();
    if (aux) {
        //returnData = {aux->getType(), aux->getId()};

        game.dropItems(std::move(aux), currentPosition);
    }
    return returnData;
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


void Player::listFrom(Coordinate npcPosition) {
    game.list(*this, npcPosition);
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
    msgpack::type::tuple<std::string> nick(Entity::getNickname());
    msgpack::pack(buffer, nick);
}

void Player::clearMinichat() {
    chat.clear();
}

void Player::addMessage(const std::string &message) {
    chat.addMessage(message);
}

void Player::move(Coordinate newPosition) {
    stats.stopMeditating(chat);
    Entity::move(newPosition);
}

void Player::restoreStats() {
    stats.restore();
}

bool Player::isDead() {
    return stats.isDead();
}

void Player::resetMovement() {
    movement.movedDistance = 0;
    movement.direction = DIRECTION_STILL;
    movement.isMoving = false;
}

bool Player::hasItem(const std::string& itemName) {
    return inventory.hasItem(itemName);
}


void Player::getInventoryNames() {
    inventory.getInventoryNames(chat);
}


PlayerData Player::getData() const {
    PlayerData pData;
    pData.nickname = getNickname();
    pData.pRace = race;
    pData.pClass = pClass;
    pData.gold = gold;
    stats.getData(pData);
    inventory.getData(pData);
    return pData;
}
