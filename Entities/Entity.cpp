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
