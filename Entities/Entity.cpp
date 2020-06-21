//
// Created by agustin on 8/6/20.
//

#include "Entity.h"
#include "../AttackResult.h"

const unsigned int DISTANCE_TO_MOVE = 500;

Entity::Entity(Coordinate initialPosition) {
    currentPosition.iPosition = initialPosition.iPosition;
    currentPosition.jPosition = initialPosition.jPosition;
    movement.movedDistance = 0;
    movement.isMoving = false;
    speed = 1;
}

void Entity::setPosition(Coordinate coordinate) {
    currentPosition = coordinate;
}

Coordinate Entity::getPosition() {
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

void Entity::move(Direction moveDirection) const {
    if (movement.isMoving) {
        switch (moveDirection) {
            case DIRECTION_UP:
                //todo invocar a metodo para moverme
                break;
            case DIRECTION_DOWN:
                //todo invocar a metodo para moverme
                break;
            case DIRECTION_RIGHT:
                //todo invocar a metodo para moverme
                break;
            case DIRECTION_LEFT:
                //todo invocar a metodo para moverme
                break;
        }
    }
}

void Entity::startMoving(Direction moveDirection) {
    switch (moveDirection) {
        case DIRECTION_UP:
            --currentPosition.iPosition;
            break;
        case DIRECTION_DOWN:
            ++currentPosition.iPosition;
            break;
        case DIRECTION_RIGHT:
            ++currentPosition.jPosition;
            break;
        case DIRECTION_LEFT:
            --currentPosition.jPosition;
            break;
    }
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
