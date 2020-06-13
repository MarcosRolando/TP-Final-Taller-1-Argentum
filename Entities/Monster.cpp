//
// Created by agustin on 7/6/20.
//

#include "Monster.h"


////////////////////////PRIVATE////////////////////////



//Intenta atacar en sus alrededores, si no encuentra un jugador a quien atacar
//no hace nada y retorna false, sino vacia pathCache, ataca y retorna true
bool Monster::_tryToAttack() {
    //return damage;
    std::vector<Coordinate> targets;
    map.getTargets();
}

//Pide al game que lo mueva a la siguiente posicion en pathCache, si pathCache
//esta vacio entonces busca el jugador mas cercano en su rango de vision y le
//pide al mapa un camino a este
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

