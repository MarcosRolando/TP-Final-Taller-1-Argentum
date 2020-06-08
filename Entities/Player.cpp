//
// Created by agustin on 8/6/20.
//

#include "Player.h"

Player::Player(unsigned int _maxHealth, unsigned int _maxMana): inventory((*this)) {
    maxHealth = _maxHealth;
    maxMana = _maxMana;

}
