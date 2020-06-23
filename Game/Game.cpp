//
// Created by agustin on 7/6/20.
//

#include <algorithm>
#include "Game.h"
#include "../AttackResult.h"
#include "../Entities/Monster.h"
#include "ShouldMonsterBeRemoved.h"

/////////////////////////////////PRIVATE//////////////////////////



//Carga hasta monsterCreationRate monstruos nuevos cada cierto invervalo de tiempo
//Si la cantidad que se desea crear sobrepasa la cantidad maxima, entonces crea hasta
//conseguir la cantidad maxima
void Game::_repopulateMap(double timePassed) {
    spawnTimer += static_cast<unsigned int>(timePassed);
    if (spawnTimer >= spawnInterval) {
        unsigned int monstersToCreate = monsterCreationRate;
        std::shared_ptr<Monster> monster;
        spawnTimer = 0;
        if ((monstersToCreate + monsters.size()) > maxNumberOfMonsters) {
            monstersToCreate = maxNumberOfMonsters - monsters.size();
        }
        for (unsigned int i = 0; i < monstersToCreate; ++i) {
            //Coordinate monsterPosition = map.getMonsterCoordinate();
            monstersFactory.storeRandomMonster(*this, monster);
            monsters.push_back(monster);
            map.addEntity(map.getMonsterCoordinate(), std::static_pointer_cast<Entity>(monster));
        }
    }
}


void Game::_executeQueueOperations() {
    MoveCommand aux{};
    while (!eventQueue.empty()) {
        aux = eventQueue.front();
        eventQueue.pop();
        map.moveEntity(aux.initialPosition, aux.finalPosition);
        //TOMAR EN CUENTA QUE VAMOS A TENER QUE ENCOLAR
        //CADA MOVIMIENTO REALIZADO PARA MANDARSELO A LOS CLIENTES
        //PARA ESTO ESTA EL BOOL DEL STRUCT
    }
}


void Game::_updateMonsters(double timeStep) {
    for (const auto & monster: monsters) {
        monster->update(timeStep);
    }
}

//Elimina de las listas almacenadas y del mapa los players y monsters que deban ser eliminados
void Game::_removeEntities() {
    std::list<Coordinate> monstersToRemove;
    ShouldMonsterBeRemoved sholdBeRemoved(monstersToRemove);
    monsters.erase(std::remove_if(monsters.begin(), monsters.end(), sholdBeRemoved), monsters.end());
    for (const auto & coordinate: monstersToRemove) {
        map.removeEntity(coordinate);
    }

    //AGREGAR BORRADO DE PLAYER_HANDLERS
}

/////////////////////////////////PUBLIC//////////////////////////

AttackResult Game::attackPosition(int damage, unsigned int level, bool isAPlayer,
                                    Coordinate coordinate) {
    return map.attackTile(damage, level, isAPlayer, coordinate);
}

void Game::dropItems(std::list<std::shared_ptr<Item>>&& items, Coordinate position) {
    map.addItemsToTile(std::move(items), position);
}

void Game::dropItems(std::shared_ptr<Item> &&item, Coordinate position) {
    map.addItemsToTile(std::move(item), position);
}

void Game::requestMove(Coordinate initialPosition, Coordinate finalPosition) {
    if (map.isPlaceAvailable(finalPosition)) {
        eventQueue.push({initialPosition, finalPosition, false});
    }
}

void Game::update(double timeStep) {
    _repopulateMap(timeStep);
    _updateMonsters(timeStep);
    _executeQueueOperations();

    //AGREGAR UPDATE DE PLAYERS CONECTADOS

    _removeEntities();
}

Game::Game() {
    monsterCreationRate = 20;
    maxNumberOfMonsters = 300;
    spawnInterval = 100;
    spawnTimer = 0;
    map.test(*this, monsters);
}

const Map& Game::getMap() const {
    return map;
}
