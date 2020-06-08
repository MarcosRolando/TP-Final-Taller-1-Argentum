//
// Created by agustin on 8/6/20.
//

#include "Player.h"

Player::Player(unsigned int _maxHealth, unsigned int _maxMana): inventory((*this)) {
    maxHealth = _maxHealth;
    currentHealth = _maxHealth;
    maxMana = _maxMana;
    currentMana = _maxMana;

}

void Player::movea(Direction direction) {
    /*
    switch (direction) {
        case DIRECTION_UP:
            currentPosition.iPosition;
            break;
        case DIRECTION_DOWN:
    }
    */

}
