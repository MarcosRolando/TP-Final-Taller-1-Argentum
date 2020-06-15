//
// Created by agustin on 8/6/20.
//

#include "Entity.h"

Entity::Entity(Coordinate initialPosition) {
    currentPosition.iPosition = initialPosition.iPosition;
    currentPosition.jPosition = initialPosition.jPosition;
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

unsigned int Entity::attacked(unsigned int damage, unsigned int level) {
    return 0;
}

void Entity::list(std::list<ProductData>& products) {
    //NO NOTHING
}

void Entity::withdraw(Player &player, const std::string& itemName) {
    //NO NOTHING
}

void Entity::deposit(Player &player, const std::string& itemName) {
    //NO NOTHING
}

void Entity::buy(Player &player, const std::string &itemName, unsigned int gold) {
    //NO NOTHING
}

void Entity::sell(Player &player, unsigned int itemPosition) {
    //DO NOTHING
}
