//
// Created by agustin on 7/6/20.
//

#include "Monster.h"


////////////////////////PRIVATE////////////////////////



//VER SI HACE FALTA QUE RETORNE EL DAÑO QUE VA A HACER
unsigned int Monster::_attack() {
    return damage;
}


void Monster::_move() {


    //IMPLEMENTAR

    /*
    Coordinate nearestPlayer;
    bool hasFoundPlayer = false;
    for (int i = 0; i < ; ++i) {
        for (int j = 0; j < ; ++j) {

        }
    }
     */
}


////////////////////////PUBLIC/////////////////////////

Monster::Monster(Game &_game, const Map& _map, unsigned int _health,
                 unsigned int _rangeOfVision, unsigned int _timeBetweenActions,
                 Coordinate initialPosition):
                 Entity(initialPosition), timeBetweenActions(_timeBetweenActions),
                 map(_map), game(_game) {
    health = _health;
    rangeOfVision = _rangeOfVision;
    timeBetweenActions = _timeBetweenActions;
    timer = time(0);
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

void Monster::act() {
    unsigned long currentTime = time(0);
    if (currentTime - timer >= timeBetweenActions) {
        //HACER CHEQUEO PARA VER SI ME TENGO QUE MOVER O SI TENGO QUE ATACAR

        timer = currentTime;
    }
}

