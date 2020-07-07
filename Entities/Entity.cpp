//
// Created by agustin on 8/6/20.
//

#include "Entity.h"
#include "../AttackResult.h"
#include "../Game/Game.h"
#include "../Game/Events/Move.h"
#include "../Config/GameEnums.h"
#include "../Game/Events/Moved.h"
#include <msgpack.hpp>

MSGPACK_ADD_ENUM(GameType::EventID)
MSGPACK_ADD_ENUM(GameType::Entity)
MSGPACK_ADD_ENUM(GameType::Direction)

const unsigned int DISTANCE_TO_MOVE = 2000;

unsigned int Entity::availableId = 0;

Entity::Entity(GameType::Entity _type, Coordinate initialPosition, std::string&& _nicknamePrefix,
               bool isPrefixUnique /*= false*/) {
    currentPosition.iPosition = initialPosition.iPosition;
    currentPosition.jPosition = initialPosition.jPosition;
    movement.movedDistance = 0;
    movement.isMoving = false;
    movement.direction = GameType::DIRECTION_STILL;
    speed = 5;
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

/*
unsigned int Entity::list(const Player &player, std::list<ProductData>& products) {
    return 0;
}
*/
void Entity::list(Player &player) {

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

void Entity::move(Coordinate newPosition) {
    currentPosition = newPosition;
    movement.isMoving = true;
    //movement.movedDistance = 0;
}

void Entity::update(double timeStep, Game& game) {
    if (movement.isMoving) {
        std::unique_ptr<Moved> event(new Moved(*this, movement.direction,
                                       static_cast<unsigned int>(timeStep) * speed));
        game.pushEvent(std::move(event));
    }
}

bool Entity::isMoving() const {
    return movement.isMoving;
}

int32_t Entity::attack(Coordinate target) {
    return -1;
}

GameType::Entity Entity::getType() const {
    return type;
}

void Entity::operator>>(std::stringstream& buffer) const {
    msgpack::type::tuple<GameType::EventID> idType(GameType::EventID::CREATE_ENTITY);
    msgpack::pack(buffer, idType);
    msgpack::type::tuple<GameType::Entity, std::string>
                                            idData(type, nickname);
    msgpack::pack(buffer, idData);

    Coordinate previousPosition = _calculatePreviousPosition();
    msgpack::type::tuple<int32_t, int32_t, GameType::Direction, int32_t> currentMovementData(previousPosition.iPosition,
            previousPosition.jPosition, movement.direction, movement.movedDistance);

    msgpack::pack(buffer, currentMovementData);
}

bool Entity::isCitizen() {
    return (type == GameType::Entity::BANKER) || (type == GameType::Entity::TRADER) ||
           (type == GameType::Entity::PRIEST);
}

const std::string &Entity::getNickname() const {
    return nickname;
}

int32_t Entity::executeDisplacement(int32_t displacement, bool& hasFinished) {
    int32_t realDisplacement = displacement;
    movement.movedDistance += displacement;
    hasFinished = false;
    if (movement.movedDistance >= DISTANCE_TO_MOVE) {
        realDisplacement = displacement - (movement.movedDistance - DISTANCE_TO_MOVE);
        movement.movedDistance = 0;
        movement.direction = GameType::DIRECTION_STILL;
        movement.isMoving = false;
        hasFinished = true;
    }
    return realDisplacement;
}

Coordinate Entity::getFinalCoordinate(GameType::Direction moveDirection) {
    if (!isMoving()) {
        std::unique_ptr<Move> event;
        movement.direction = moveDirection;
        switch (moveDirection) {
            case GameType::DIRECTION_UP:
                return {currentPosition.iPosition - 1, currentPosition.jPosition};
            case GameType::DIRECTION_DOWN:
                return {currentPosition.iPosition + 1, currentPosition.jPosition};
            case GameType::DIRECTION_RIGHT:
                return {currentPosition.iPosition, currentPosition.jPosition + 1};
            case GameType::DIRECTION_LEFT:
                return {currentPosition.iPosition, currentPosition.jPosition - 1};
            case GameType::DIRECTION_STILL:
                //do nothing
                break;
        }
    }
    return {-1, -1};
}


///////////////////////////////////PUBLIC///////////////////////////////////
//Calcula la posicion previa tomando en cuenta la direccion de movimiento y la
//posicion actual
Coordinate Entity::_calculatePreviousPosition() const {
    Coordinate previous = currentPosition;
    switch (movement.direction) {
        case GameType::DIRECTION_UP:
            previous.iPosition++;
            break;
        case GameType::DIRECTION_DOWN:
            previous.iPosition--;
            break;
        case GameType::DIRECTION_LEFT:
            previous.jPosition++;
            break;
        case GameType::DIRECTION_RIGHT:
            previous.jPosition--;
            break;
        case GameType::DIRECTION_STILL:
            //DO NOTHING
            break;
    }
    return previous;
}