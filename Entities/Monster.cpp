//
// Created by agustin on 7/6/20.
//

#include "Monster.h"

#define MAX_NUMBER_OF_CACHED_NODES 4

////////////////////////PRIVATE////////////////////////

//Retorna la distancia (siempre positiva) entre las dos coordenadas
unsigned int Monster::_getDistance(Coordinate a, Coordinate b) {
    return std::abs((a.iPosition - b.iPosition) + (a.jPosition - b.jPosition));
}

/*
//Retorna la coordenada a menor distancia de refference, no deberia ser llamada
//en un vector vacio
Coordinate Monster::_getNearestPosition(Coordinate refference, std::vector<Coordinate> positions) {
    Coordinate nearest = positions[0];
    unsigned int minDistance = _getDistance(refference, nearest);
    unsigned int aux;
    for (int i = 0; i < positions.size(); ++i) {
        aux = _getDistance(refference, positions[i]);
        if (aux < minDistance) {
            aux = minDistance;
            nearest = positions[i];
        }
    }
    return nearest;
}
*/

//Guarda parte del camino al jugador al cual tiene que moverse la menor cantidad
//de veces para alcanzarlo
void Monster::_storeNearestPlayerPathCache() {
    unsigned int nearestTargetIndex = 0;
    std::vector<Coordinate> positions;
    map.getTargets(currentPosition, rangeOfVision, positions);
    if (positions.size() != 0) {
        std::vector<std::list<Coordinate>> allPaths/*(positions.size())*/;
        std::list<Coordinate> aux;
        for (auto & position : positions) {
            if (map.getPath(currentPosition, position, aux)) {
                allPaths.push_back(std::move(aux));
                if (allPaths[allPaths.size() - 1].size() < allPaths[nearestTargetIndex].size()) {
                    nearestTargetIndex = allPaths.size() - 1;
                }
                aux.clear();
            }
        }
        pathCache = std::move(allPaths[nearestTargetIndex]);
        if (pathCache.size() > MAX_NUMBER_OF_CACHED_NODES) {
            pathCache.resize(MAX_NUMBER_OF_CACHED_NODES);
        }
    }
}

//Intenta atacar en sus alrededores, si no encuentra un jugador a quien atacar
//no hace nada y retorna false, sino vacia pathCache, ataca y retorna true
bool Monster::_tryToAttack() {
    std::vector<Coordinate> targets;
    map.getTargets(currentPosition, rangeOfVision, targets);
    for (auto & target : targets) {
        if (_getDistance(currentPosition, target) == 1) {
            game.attackPosition(damage, level, target);
            pathCache.clear();
            return true;
        }
    }
    return false;
}



//Pide al game que lo mueva a la siguiente posicion en pathCache, si pathCache
//esta vacio entonces busca el jugador mas cercano en su rango de vision y le
//pide al mapa un camino a este
//Si la proxima posicion a la que se va a mover esta ocupada entonces vuelve a
//calcular el camino al jugador mas cercano (esto puede pasar si un monstruo se
//pone en su camino)
void Monster::_move() {
    if (!map.isPlaceAvailable(pathCache.front())) {
        pathCache.clear();
    }
    if (pathCache.empty()) {
        _storeNearestPlayerPathCache();
    }

    //IMPLEMENTAR EL PEDIDO A GAME PARA CAMBIAR DE POSICION

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
    level = 0;
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
        if (!_tryToAttack()) {
            _move();
        }
        timer = currentTime;
    }
}


