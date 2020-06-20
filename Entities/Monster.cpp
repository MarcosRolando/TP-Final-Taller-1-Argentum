//
// Created by agustin on 7/6/20.
//

#include "Monster.h"
#include "../Config/Calculator.h"
#include "../Items/ItemsFactory.h"
#include "../Game.h"
#include "../AttackResult.h"

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
    if (!positions.empty()) {
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

Direction Monster::_getMoveDirection() {
    Coordinate destiny = pathCache.front();
    Coordinate difference = {destiny.iPosition - currentPosition.iPosition,
                             destiny.jPosition - currentPosition.jPosition};
    if (difference.iPosition  == 1) {
        return DIRECTION_DOWN;
    } else if (difference.iPosition == -1) {
        return DIRECTION_UP;
    } else if (difference.jPosition == -1) {
        return DIRECTION_LEFT;
    } else {
        return DIRECTION_RIGHT;
    }
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
    Entity::move(_getMoveDirection());
}


////////////////////////PUBLIC/////////////////////////

Monster::Monster(Game &_game, const Map& _map, int _life,
                 unsigned int _rangeOfVision, unsigned int _timeBetweenActions,
                 Coordinate initialPosition):
                 Entity(initialPosition), timeBetweenActions(_timeBetweenActions),
                 map(_map), game(_game) {
    maxLife = _life;
    currentLife = maxLife;
    rangeOfVision = _rangeOfVision;
    timer = time(nullptr);
    level = 0;
    damage = 0; //todo no estaria haciendo nada de danio xd
}


AttackResult Monster::attacked(int _damage, unsigned int attackerLevel) {
    if (!isDead()) {
        currentLife -= _damage;
        if (currentLife < 0) {
            currentLife = 0;
            std::shared_ptr<Item> drop;
            ItemsFactory::getInstance().storeRandomDrop(drop, maxLife);
            game.dropItems(std::move(drop), currentPosition);
        }
        unsigned int experience = Calculator::calculateAttackXP(damage,
                                                                attackerLevel, level);
        if (isDead() && damage > 0) {
            experience += Calculator::calculateKillXP(attackerLevel, level, maxLife);
        }
        return {_damage, experience};
    }
    return {0, 0};
}

bool Monster::isDead() const {
    return currentLife == 0;
}

void Monster::act() {
    unsigned long currentTime = time(0); //todo esto recibe un puntero time_t donde lo guarda, no 0
    if (currentTime - timer >= timeBetweenActions) {
        if (!_tryToAttack() && !isMoving()) {
            _move();
        }
        timer = currentTime;
    }
}

std::shared_ptr<Item> Monster::dropLoot() {
    return std::shared_ptr<Item>();
}

