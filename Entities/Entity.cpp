//
// Created by agustin on 8/6/20.
//

#include "Entity.h"
#include "../AttackResult.h"
#include "../Game/Game.h"
#include "../Game/Events/Move.h"
#include "../Config/GameEnums.h"
#include <msgpack.hpp>

MSGPACK_ADD_ENUM(GameType::ID)
MSGPACK_ADD_ENUM(GameType::Entity)

const unsigned int DISTANCE_TO_MOVE = 500;

unsigned int Entity::availableId = 0;

Entity::Entity(GameType::Entity _type, Coordinate initialPosition, std::string&& _nicknamePrefix,
               bool isPrefixUnique /*= false*/) {
    currentPosition.iPosition = initialPosition.iPosition;
    currentPosition.jPosition = initialPosition.jPosition;
    movement.movedDistance = 0;
    movement.isMoving = false;
    speed = 2;
    type = _type;
    nickname = std::move(_nicknamePrefix);
    if (!isPrefixUnique) {
        nickname += std::to_string(availableId);
        availableId++;
    }
}

void Entity::setPosition(Coordinate coordinate) {
    currentPosition = coordinate;
}

Coordinate Entity::getPosition() const {
    return currentPosition;
}

bool Entity::isMonsterTarget() {
    return false;
}

AttackResult Entity::attacked(int damage, unsigned int level, bool isAPlayer) {
    return {0, 0};
}

unsigned int Entity::list(const Player &player, std::list<ProductData>& products) {
    return 0;
}

void Entity::withdraw(Player &player, const std::string& itemName) {
    //NO NOTHING
}

void Entity::deposit(Player &player, const std::string& itemName) {
    //NO NOTHING
}

void Entity::buy(Player &player, const std::string &itemName) {
    //NO NOTHING
}

void Entity::sell(Player &player, const std::string& itemName) {
    //DO NOTHING
}

void Entity::requestMove(Game& game, Direction moveDirection) {
    if (!isMoving()) {
        std::unique_ptr<Move> event;
        switch (moveDirection) {
            case DIRECTION_UP:
                event.reset(new Move(game, *this, {currentPosition.iPosition - 1,
                                                                    currentPosition.jPosition} ));
                game.pushEvent(std::move(event));
                break;
            case DIRECTION_DOWN:
                event.reset(new Move(game, *this, {currentPosition.iPosition + 1,
                                                                   currentPosition.jPosition} ));
                game.pushEvent(std::move(event));
                break;
            case DIRECTION_RIGHT:
                event.reset(new Move(game, *this, {currentPosition.iPosition,
                                                                   currentPosition.jPosition + 1} ));
                game.pushEvent(std::move(event));
                break;
            case DIRECTION_LEFT:
                event.reset(new Move(game, *this, {currentPosition.iPosition,
                                                   currentPosition.jPosition - 1} ));
                game.pushEvent(std::move(event));
                break;
        }
    }
}

void Entity::move(Coordinate newPosition) {
    currentPosition = newPosition;
    movement.isMoving = true;
    movement.movedDistance = 0;
}

void Entity::update(double timeStep) {
    if (movement.isMoving) {
        movement.movedDistance += static_cast<unsigned int>(timeStep) * speed;
        if (movement.movedDistance >= DISTANCE_TO_MOVE) {
            movement.movedDistance = DISTANCE_TO_MOVE;
            movement.isMoving = false;
        }
    }
}

bool Entity::isMoving() const {
    return movement.isMoving;
}

void Entity::attack(Coordinate target) {}


GameType::Entity Entity::getType() const {
    return type;
}

void Entity::operator>>(std::stringstream& buffer) {
    msgpack::type::tuple<GameType::ID> idType(GameType::ID::ENTITY);
    msgpack::type::tuple<GameType::Entity, std::string, uint32_t, uint32_t>
                                            data(type, nickname, currentPosition.iPosition,
                                                        currentPosition.jPosition);
    msgpack::pack(buffer, idType);
    msgpack::pack(buffer, data);
}

bool Entity::isCitizen() {
    return (type == GameType::Entity::BANKER) || (type == GameType::Entity::TRADER) ||
           (type == GameType::Entity::PRIEST);
}

const std::string &Entity::getNickname() {
    return nickname;
}
