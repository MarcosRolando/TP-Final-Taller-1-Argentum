//
// Created by agustin on 8/6/20.
//

#include "Player.h"
#include "../Config/Calculator.h"
#include "AttackResult.h"
#include "../Game/Game.h"
#include "../Items/Miscellaneous/Gold.h"
#include "../Game/Events/Drop.h"
#include "../Game/Events/NotifyDeath.h"
#include "../Game/Events/Move.h"
#include <msgpack.hpp>

#define ATTACKER_IS_NEWBIE_MESSAGE "I won't lose my time on a low level newbie like you!\n"
#define PLAYER_IS_A_NEWBIE_MESSAGE "Surely you have better things to do than attack a low level newbie like me...\n"
#define PLAYER_IS_DEAD_MESSAGE "You can't kill a ghost, you know?\n"
#define DODGED_ATTACK_MESSAGE "You dodged an attack\n"
#define GHOSTS_CANT_RESTORE_STATS_MESSAGE "Ghosts can't restore stats\n"
#define WARRIOR_CANT_MEDITATE_MESSAGE "You are a Warrior and Warriors cannot meditate!\n"

using namespace GameType;

MSGPACK_ADD_ENUM(GameType::Race)
MSGPACK_ADD_ENUM(GameType::EventID)

////////////////////////////////////PUBLIC///////////////////////////////

Player::Player(Game& _game, Coordinate _initialPosition, const PlayerData& data):
               Entity(GameType::Entity::PLAYER, _initialPosition, data.nickname, true),
               inventory(data),
               stats(data),
               game(_game) {

    speed = Configuration::getInstance().configPlayerSpeed();
    pClass = data.pClass;
    race = data.pRace;
    gold = data.gold;
    movementBackup = {false, GameType::DIRECTION_STILL};
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
        return _receiveDamage(damage, attackerLevel, isAPlayer);
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
    } else {
        chat.addMessage(GHOSTS_CANT_RESTORE_STATS_MESSAGE);
    }
}

void Player::restoreMana(unsigned int amount) {
    if (!stats.isDead()) {
        stats.restoreMana(amount);
    } else {
        chat.addMessage(GHOSTS_CANT_RESTORE_STATS_MESSAGE);
    }
}

void Player::meditate() {
    if (!stats.isDead()) {
        if (pClass != GameType::WARRIOR) {
            stats.startMeditating(chat);
        } else {
            addMessage(WARRIOR_CANT_MEDITATE_MESSAGE);
        }
    }
}

void Player::update(double timeStep) {
    Entity::update(timeStep, game); /*actualiza movimiento*/
    if (!movement.isMoving && movementBackup.isFollowingRoad) {
        game.pushEvent(std::unique_ptr<Event>(new Move(game, *this,
                        movementBackup.direction)));
    }
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

const Item* Player::dropItem(unsigned int itemPosition) {
    std::shared_ptr<Item> aux = inventory.removeItem(itemPosition);
    const Item* returnData = aux.get();
    if (aux) {
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
    msgpack::type::tuple<int32_t, int32_t> data(gold, Calculator::calculateMaxSafeGold(stats.getLevel()));
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

void Player::restoreStats(bool isBeingRevived) {
    //if ((esta vivo y no pide que lo resuciten) || (pide que lo resuciten y esta muerto)))
    //Esta funcion se usa para curar y para cuando se resucite, se chequea para que no se cure
    //cuando llame a resucitar si es que esta vivo y para que no resucite si esta vivo
    if ((!stats.isDead() && !isBeingRevived) || (isBeingRevived && stats.isDead())) {
        stats.restore();
    }
    if (stats.isDead() && !isBeingRevived) {
        chat.addMessage(GHOSTS_CANT_RESTORE_STATS_MESSAGE);
    }
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

void Player::startMovement(GameType::Direction direction) {
    movementBackup.isFollowingRoad = true;
    movementBackup.direction = direction;
}

void Player::stopMovement() {
    movementBackup.isFollowingRoad = false;
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

void Player::_storeAttackedResultMessage(std::string& resultMessage, std::pair<int, bool> attackResult,
                                  unsigned int experience) {
    std::string damageString = std::to_string(attackResult.first);
    if (attackResult.second) {
        resultMessage += getNickname() + " dodged your attack\n";
    } else {
        resultMessage += "You damaged " + getNickname() + " by " + damageString;
        resultMessage += " (Remaining Life: " + std::to_string(stats.getCurrentLife()) +
                           " , XP Gained: " + std::to_string(experience) + ")\n";
    }
    if (attackResult.second) {
        chat.addMessage(DODGED_ATTACK_MESSAGE);
    } else if (attackResult.first >= 0) {
        chat.addMessage("You lost " + damageString + " health points\n");
    } else if (attackResult.first < 0) {
        chat.addMessage("You healed " + damageString + " health points\n");
    }
}

AttackResult Player::_receiveDamage(int damage, unsigned int attackerLevel, bool isAPlayer) {
    std::string attackedMessage;
    unsigned int defense = inventory.getDefense();
    std::pair<int, bool> result = stats.modifyLife(damage, attackerLevel, defense, isAPlayer, attackedMessage);
    unsigned int experience = Calculator::calculateAttackXP(result.first,
                                                            attackerLevel, stats.getLevel());
    if (stats.isDead() && result.first > 0) {
        _dropItems();
        experience += Calculator::calculateKillXP(attackerLevel,
                                                  stats.getLevel(), stats.getMaxLife());
        game.pushEvent(std::unique_ptr<Event>(new NotifyDeath(*this)));
    }
    _storeAttackedResultMessage(attackedMessage, result, experience);
    return {result.first, experience, std::move(attackedMessage)};
}
