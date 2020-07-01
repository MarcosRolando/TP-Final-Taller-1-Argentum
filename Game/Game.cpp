//
// Created by agustin on 7/6/20.
//

#include <algorithm>
#include "Game.h"
#include "../AttackResult.h"
#include "../Entities/Monster.h"
#include "ShouldMonsterBeRemoved.h"
#include "Events/Event.h"
#include "../Server/ServerProtocol.h"
#include "../Entities/Player.h"

#include <iostream>


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
            //map.addEntity({0, 0}, std::shared_ptr<Entity>(new Monster(*this, {0, 0}, GameType::Entity::SKELETON)));
            monstersFactory.storeRandomMonster(*this, monster);
            monsters.push_back(monster);
            map.addEntity(map.getMonsterCoordinate(), std::static_pointer_cast<Entity>(monster));
        }
    }
}

void Game::_executeQueueOperations(ServerProtocol& protocol) {
    while (!eventQueue.empty()) {
        (*eventQueue.front())(protocol);
        eventQueue.pop();

        //TOMAR EN CUENTA QUE VAMOS A TENER QUE ENCOLAR
        //CADA ACCION REALIZADA PARA MANDARSELA A LOS CLIENTES
    }
}

void Game::moveEntity(Coordinate initialPosition, Coordinate finalPosition) {
    map.moveEntity(initialPosition, finalPosition);
}

void Game::_updateMonsters(double timeStep) {
    for (const auto & monster: monsters) {
        monster->update(timeStep);
    }
}

void Game::_updatePlayers(double timeStep) {
    for (const auto & player: players) {
        player->update(timeStep);
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



void Game::update(double timeStep, ServerProtocol& protocol) {
    _repopulateMap(timeStep);
    _updateMonsters(timeStep); //todo pasar a lista de Monster* en vez de shared ptr
    _updatePlayers(timeStep);
    clients.update(); //todo cambiar el nombre a mergeo de eventos
    _executeQueueOperations(protocol);

    //AGREGAR UPDATE DE PLAYERS CONECTADOS

    _removeEntities();
}

Game::Game(MapFileReader&& mapFile, ClientsMonitor& _clients): map(mapFile), clients(_clients) {
    monsterCreationRate = 20;
    maxNumberOfMonsters = 300;
    spawnInterval = 100;
    spawnTimer = 0;
}

const Map& Game::getMap() const {
    return map;
}

unsigned int Game::list(Player &player, std::list<ProductData> &products, Coordinate coordinate) {
    return map.list(player, products, coordinate);
}

void Game::withdraw(Player &player, const std::string &itemName, Coordinate coordinate) {
    map.withdraw(player, itemName, coordinate);
}

void Game::deposit(Player &player, const std::string &itemName, Coordinate coordinate) {
    map.deposit(player, itemName, coordinate);
}

void Game::buy(Player &player, const std::string &itemName, Coordinate coordinate) {
    map.buy(player, itemName, coordinate);
}

void Game::sell(Player &player, const std::string &itemName, Coordinate coordinate) {
    map.sell(player, itemName, coordinate);
}

void Game::pushEvent(std::unique_ptr<Event>&& event) {
    eventQueue.push(std::move(event));
}

Game::Game(ClientsMonitor&& clientAux /*= ClientsMonitor()*/): clients(clientAux) {

}

Player& Game::createPlayer(std::string &&nickname, GameType::Race race,
                GameType::Class _class, ServerProtocol& protocol) {
    //todo ver si lo spawneamos en un area especifica tipo la capital o pueblos
    int x = 0;
    Coordinate position{};
    while (true) { //esto es solo por ahora para generar al player en el primer tile disponible
        position = {0, x};
        if (map.isPlaceAvailable(position)) break;
        ++x;
    }
    std::shared_ptr<Player> player(new Player(*this, race, _class, 1,
                                0, position, std::move(nickname)));
    Player* playerAux = player.get();
    players.emplace_back(playerAux);
    map.addEntity(position, std::move(player));
    std::stringstream data;
    (*playerAux) >> data;
    protocol.addToGeneralData(data);
    return *playerAux;
}
