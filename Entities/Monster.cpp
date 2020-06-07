//
// Created by agustin on 7/6/20.
//

#include "Monster.h"

unsigned int Monster::attack() {
    return damage;
}

void Monster::attacked(unsigned int _damage) {
    health -= _damage;
    if (health < 0) {
        health = 0;
    }
}

bool Monster::isDead() {
    return health == 0;
}
