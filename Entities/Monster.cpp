//
// Created by agustin on 7/6/20.
//

#include "Monster.h"


////////////////////////PRIVATE////////////////////////



////////////////////////PUBLIC/////////////////////////


//VER SI HACE FALTA QUE RETORNE EL DAÑO QUE VA A HACER
unsigned int Monster::attack() {
    return damage;
}


void Monster::move() {
    Coordinate nearestPlayer;
    bool hasFoundPlayer = false;
    for (int i = 0; i < ; ++i) {
        for (int j = 0; j < ; ++j) {

        }
    }
}


unsigned int Monster::attacked(unsigned int _damage, unsigned int level) {
    health -= _damage;
    if (health < 0) {
        health = 0;
    }
    return damage;
}

bool Monster::isDead() {
    return health == 0;
}

Monster::Monster(Game &_game, const Map& _map, unsigned int _health,
                 unsigned int _rangeOfVision, Coordinate initialPosition):
                 Entity(initialPosition), map(_map), game(_game) {
    health = _health;
    rangeOfVision = _rangeOfVision;
}

