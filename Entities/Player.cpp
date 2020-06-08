//
// Created by agustin on 8/6/20.
//

#include "Player.h"



////////////////////////////////////PUBLIC///////////////////////////////

Player::Player(unsigned int _maxHealth, unsigned int _maxMana): inventory((*this)) {
    maxHealth = _maxHealth;
    currentHealth = _maxHealth;
    maxMana = _maxMana;
    currentMana = _maxMana;

}

void Player::move(Direction direction) {
    switch (direction) {
        case DIRECTION_UP:
            currentPosition.jPosition--;
            break;
        case DIRECTION_DOWN:
            currentPosition.jPosition++;
            break;
        case DIRECTION_LEFT:
            currentPosition.iPosition++;
            break;
        case DIRECTION_RIGHT:
            currentPosition.iPosition--;
            break;
    }
}

void Player::attack(Coordinate target) {
    //IMPLEMENTAR
}

