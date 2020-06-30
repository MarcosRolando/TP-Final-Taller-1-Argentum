//
// Created by agustin on 7/6/20.
//

#include "Monster.h"
#include "../Config/Calculator.h"
#include "../Items/ItemsFactory.h"
#include "../Game/Game.h"
#include "../AttackResult.h"
#include "../Config/Configuration.h"
#include "../Game/Events/Attack.h"
#include "../Game/Events/Move.h"

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
    map.getTargets(currentPosition, stats.getRangeOfVision(), positions);
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
    map.getTargets(currentPosition, stats.getRangeOfVision(), targets);
    for (auto & target : targets) {
        if (_getDistance(currentPosition, target) == 1) {
            std::unique_ptr<Attack> attackFunction(new Attack(*this, target));
            game.pushEvent(std::move(attackFunction));
            pathCache.clear();
            return true;
        }
    }
    return false;
}

GameType::Direction Monster::_getMoveDirection() {
    Coordinate destiny = pathCache.front();
    Coordinate difference = {destiny.iPosition - currentPosition.iPosition,
                             destiny.jPosition - currentPosition.jPosition};
    if (difference.iPosition  == 1) {
        return GameType::DIRECTION_DOWN;
    } else if (difference.iPosition == -1) {
        return GameType::DIRECTION_UP;
    } else if (difference.jPosition == -1) {
        return GameType::DIRECTION_LEFT;
    } else {
        return GameType::DIRECTION_RIGHT;
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
    if (!pathCache.empty()) {
        //Entity::requestMove(game, _getMoveDirection());
        game.pushEvent(std::unique_ptr<Move>(new Move(game, *this, _getMoveDirection())));
        pathCache.pop_front();
    }
}


////////////////////////PUBLIC/////////////////////////

Monster::Monster(Game &_game, Coordinate initialPosition,
                 GameType::Entity _type):
                 Entity(_type, initialPosition, "pepito"/*todo*/),
                 timeBetweenActions(Configuration::getInstance().configMonsterStats(_type).reactionSpeed * 1000),
                 stats(_type), map(_game.getMap()), game(_game) {
    elapsedTime = 0;
    type = _type;
}


AttackResult Monster::attacked(int _damage, unsigned int attackerLevel, bool isAPlayer) {
    AttackResult result = {0, 0};
    if (!isDead()) {
        if (Calculator::canDodge(stats.getAgility())) return result;
        result = stats.modifyLife(_damage, attackerLevel);
        if (isDead()) {
            std::shared_ptr<Item> drop;
            ItemsFactory::getInstance().storeRandomDrop(drop, stats.getMaxLife());
            game.dropItems(std::move(drop), currentPosition);
        }
    }
    return result;
}

void Monster::update(double timeStep) {
    Entity::update(timeStep, game);
    elapsedTime += timeStep;
    if (elapsedTime >= timeBetweenActions) {
        if (!_tryToAttack() && !isMoving()) {
            _move();
        }
        elapsedTime = 0;
    }
}

bool Monster::isDead() const {
    return (stats.getCurrentLife() == 0);
}

void Monster::attack(Coordinate attackedPosition) {
    game.attackPosition(stats.getDamage(), stats.getLevel(), false, attackedPosition);
}

