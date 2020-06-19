//
// Created by agustin on 8/6/20.
//

#include "Entity.h"

using namespace std::chrono;

Entity::Entity(Coordinate initialPosition) {
    currentPosition.iPosition = initialPosition.iPosition;
    currentPosition.jPosition = initialPosition.jPosition;
    movement.movedDistance = 0;
    movement.elapsedTime = 0;
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

AttackResult Entity::attacked(int damage, unsigned int level) {
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
    if (movement.moving) {
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

void Entity::startMoving() {
    movement.moving = true;
    movement.movedDistance = 0;
    high_resolution_clock::time_point currentTime = high_resolution_clock::now();
}