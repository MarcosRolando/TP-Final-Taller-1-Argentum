//
// Created by agustin on 7/6/20.
//

#include "Monster.h"
#include "../Items/ItemsFactory.h"
#include "../Game/Game.h"
#include "AttackResult.h"
#include "../Config/Configuration.h"
#include "../Game/Events/Attack.h"
#include "../Game/Events/Move.h"
#include "../Game/Events/Drop.h"
#include "../Config/Calculator.h"

#define MAX_NUMBER_OF_CACHED_NODES 4

////////////////////////PRIVATE////////////////////////

//Retorna la distancia (siempre positiva) entre las dos coordenadas
unsigned int Monster::_getDistance(Coordinate a, Coordinate b) {
    return std::abs(a.iPosition - b.iPosition) + std::abs(a.jPosition - b.jPosition);
}

/*Guarda parte del camino al jugador al cual tiene que moverse la menor cantidad
de veces para alcanzarlo*/
void Monster::_storeNearestPlayerPathCache() {
    unsigned int nearestTargetIndex = 0;
    std::vector<Coordinate> positions;
    map.getMoveTargets(currentPosition, stats.getRangeOfVision(), positions);
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
        if (!allPaths.empty()) {
            pathCache = std::move(allPaths[nearestTargetIndex]);
            if (pathCache.size() > MAX_NUMBER_OF_CACHED_NODES) {
                pathCache.resize(MAX_NUMBER_OF_CACHED_NODES);
            }
        }
    }
}

/*Intenta atacar en sus alrededores, si no encuentra un jugador a quien atacar
no hace nada y retorna false, sino vacia pathCache, ataca y retorna true*/
bool Monster::_tryToAttack() {
    std::vector<Coordinate> targets;
    map.getAttackTargets(currentPosition, stats.getRangeOfVision(), targets);
    for (auto & target : targets) {
        if (_getDistance(currentPosition, target) == 1) {
            std::unique_ptr<Attack> attackFunction(new Attack(*this, target));
            game.pushEvent(std::move(attackFunction));
            pathCache.clear();
            inactiveCycles = 0;
            return true;
        }
    }
    return false;
}

/*Pide al game que lo mueva a la siguiente posicion en pathCache, si pathCache
esta vacio entonces busca el jugador mas cercano en su rango de vision y le
pide al mapa un camino a este
Si la proxima posicion a la que se va a mover esta ocupada entonces vuelve a
calcular el camino al jugador mas cercano (esto puede pasar si un monstruo se
pone en su camino)*/
void Monster::_move() {
    if (!map.isPlaceAvailable(pathCache.front())) {
        pathCache.clear();
    }
    if (pathCache.empty()) {
        _storeNearestPlayerPathCache();
    }
    if (!pathCache.empty()) {
        game.pushEvent(std::unique_ptr<Move>(new Move(game, *this,
                _getMoveDirection(pathCache.front()))));
        pathCache.pop_front();
        inactiveCycles = 0;
    } else if (inactiveCycles >= 10) {
        Coordinate newPosition = map.getMonsterRandomPosition(currentPosition);
        Coordinate noPositions = {-1, -1};
        if (newPosition != noPositions) {
            game.pushEvent(std::unique_ptr<Move>(new Move(game, *this,
                    _getMoveDirection(newPosition))));
        }
        inactiveCycles = 0;
    }
}


////////////////////////PUBLIC/////////////////////////

Monster::Monster(Game &_game, Coordinate initialPosition,
                 GameType::Entity _type, GameType::Weapon _weapon):
                 Entity(_type, initialPosition, "Monster"),
                 timeBetweenActions(Configuration::getInstance().configMonsterStats(_type).reactionSpeed * 200),
                 stats(_type), map(_game.getMap()), game(_game) {
    monsterWeapon = _weapon;
    elapsedTime = 0;
    inactiveCycles = 0;
    type = _type;
    speed = Configuration::getInstance().configMonsterStats(_type).speed;
}

AttackResult Monster::attacked(int _damage, unsigned int attackerLevel, bool isAPlayer) {
    AttackResult result{0, 0, ""};
    if (_damage <= 0) return result;
    if (!isDead()) {
        bool isCritical = Calculator::isCritical();
        if (isCritical) {
            _damage *= 2;
            result.resultMessage += "Critical attack. ";
        }
        std::pair<int, bool> realAttackResult = stats.modifyLife(_damage);
        if (realAttackResult.second) {
            result.resultMessage += "The monster dodged your attack\n";
        } else {
            unsigned int experience = Calculator::calculateKillXP(attackerLevel,
                        stats.getLevel(), stats.getMaxLife());
            result = {realAttackResult.first, experience, ""};
            result.resultMessage += "You damaged the Monster by " +
                                    std::to_string(result.damage) + " (Remaining Life: " +
                                    std::to_string(stats.getCurrentLife()) +
                                    " , XP Gained: " + std::to_string(result.experience) + ")\n";
        }
        if (isDead()) {
            std::shared_ptr<Item> drop;
            ItemsFactory::getInstance().storeRandomDrop(drop, stats.getMaxLife());
            if (drop) {
                game.pushEvent(std::unique_ptr<Event>(new Drop(game,
                        std::move(drop), currentPosition)));
            }
        }
    }
    return result;
}

void Monster::update(double timeStep) {
    Entity::update(timeStep, game);
    elapsedTime += timeStep;
    if (elapsedTime >= timeBetweenActions) {
        elapsedTime = 0;
        ++inactiveCycles;
        if (!_tryToAttack() && !isMoving()) {
            _move();
        }
    }
}

bool Monster::isDead() const {
    return (stats.getCurrentLife() == 0);
}

int32_t Monster::attack(Coordinate attackedPosition) {
    game.attackPosition(stats.getDamage(), stats.getLevel(), false, attackedPosition);
    return monsterWeapon;
}

