//
// Created by agustin on 8/6/20.
//

#include "Entity.h"
#include "../AttackResult.h"
#include "../Game/Game.h"
#include "../Game/Events/Move.h"

const unsigned int DISTANCE_TO_MOVE = 500;

Entity::Entity(Coordinate initialPosition) {
    currentPosition.iPosition = initialPosition.iPosition;
    currentPosition.jPosition = initialPosition.jPosition;
    movement.movedDistance = 0;
    movement.isMoving = false;
    speed = 2;
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

void Entity::requestMove(Game& game, Direction moveDirection) const {
    if (!isMoving()) {
        switch (moveDirection) {
            case DIRECTION_UP:
                std::unique_ptr<Move> event(new Move(game, *this, {currentPosition.iPosition - 1,
                                                                    currentPosition.jPosition} ));
                game.pushEvent(game, *this, );
                game.requestMove(currentPosition,
                        {currentPosition.iPosition - 1,
                         currentPosition.jPosition});
                break;
            case DIRECTION_DOWN:
                //todo encolar functor move
                game.requestMove(currentPosition,
                                 {currentPosition.iPosition + 1,
                                  currentPosition.jPosition});
                break;
            case DIRECTION_RIGHT:
                //todo encolar functor move
                game.requestMove(currentPosition,
                                 {currentPosition.iPosition,
                                  currentPosition.jPosition + 1});
                break;
            case DIRECTION_LEFT:
                //todo encolar functor move
                game.requestMove(currentPosition,
                                 {currentPosition.iPosition,
                                  currentPosition.jPosition - 1});
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
