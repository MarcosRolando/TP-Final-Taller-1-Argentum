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

void Entity::move() {

}
