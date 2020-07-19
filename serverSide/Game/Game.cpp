//
// Created by agustin on 7/6/20.
//

#include <algorithm>
#include "Game.h"
#include "../Entities/AttackResult.h"
#include "../Entities/Monster.h"
#include "ShouldMonsterBeRemoved.h"
#include "Events/Event.h"
#include "../Server/ServerProtocol.h"
#include "../Entities/Player.h"
#include "ShouldPlayerBeRevived.h"
#include <iostream>
#include "../Server/PlayerData.hpp"
#include "../Entities/Citizens/Banker.h"
#include "../Config/Configuration.h"

MSGPACK_ADD_ENUM(GameType::EventID)

#define WAITING_TIME_MESSAGE "The estimated waiting time to resurrect is "
#define NO_PLAYER_MESSAGE "That player does not exist or is not connected\n"
#define WELCOME_MESSAGE "Welcome to Argentum traveller!\nWe hope you enjoy our work\nSincerely, AIM Team\n"
const Coordinate defaultSpawnPoint = {88,83};


/////////////////////////////////PRIVATE//////////////////////////


//Carga hasta monsterCreationRate monstruos nuevos cada cierto invervalo de tiempo
//Si la cantidad que se desea crear sobrepasa la cantidad maxima, entonces crea hasta
//conseguir la cantidad maxima
void Game::_repopulateMap(ServerProtocol& protocol) {
    Coordinate aux{};
    std::stringstream data;
    double timePassed = monsterSpawnTimer.getTime();
    if (timePassed >= spawnInterval) {
        unsigned int monstersToCreate = monsterCreationRate;
        std::shared_ptr<Monster> monster;
        monsterSpawnTimer.start();
        if ((monstersToCreate + monsters.size()) > maxNumberOfMonsters) {
            monstersToCreate = maxNumberOfMonsters - monsters.size();
        }
        for (unsigned int i = 0; i < monstersToCreate; ++i) {
            monstersFactory.storeRandomMonster(*this, monster);
            aux = map.getMonsterCoordinate();
            monster->setPosition(aux);
            (*monster) >> data;
            monsters.push_back(monster.get());
            map.addEntity(aux, std::static_pointer_cast<Entity>(monster));
        }
        protocol.addToGeneralData(data);
    }
}

//Vacia la cola de operaciones a realizar, ejecutando cada operacion que es
//desencolada
void Game::_executeQueueOperations(ServerProtocol& protocol) {
    while (!eventQueue.empty()) {
        (*eventQueue.front())(protocol);
        eventQueue.pop();
    }
}

void Game::moveEntity(Coordinate initialPosition, Coordinate finalPosition) {
    map.moveEntity(initialPosition, finalPosition);
}

//Llama a update de todos los monstruos que se encuentran en el mapa, haciendo
//que tomen una decision
void Game::_updateMonsters(double timeStep) {
    for (const auto & monster: monsters) {
        monster->update(timeStep);
    }
}

//Hace un update de los players conectados, actualizando su vida, mana y distancia
//recorrida
void Game::_updatePlayers(double timeStep) {
    for (const auto & player: players) {
        player.second->update(timeStep);
    }
}

//Elimina de las listas almacenadas y del mapa los monsters que deban ser eliminados
//y guarda en el protocolo el mensaje de que estos deben desaparecer para mandar al cliente
void Game::_removeMonsters(ServerProtocol& protocol) {
    std::stringstream data;
    std::list<std::pair<Coordinate, const std::string*>> monstersToRemove;
    ShouldMonsterBeRemoved sholdBeRemoved(monstersToRemove);
    monsters.erase(std::remove_if(monsters.begin(), monsters.end(), sholdBeRemoved), monsters.end());
    for (const auto & monster: monstersToRemove) {
        msgpack::type::tuple<GameType::EventID> eventIdData(GameType::EventID::REMOVE_ENTITY);
        msgpack::pack(data, eventIdData);
        msgpack::type::tuple<std::string>
                removedMonsterNickname(*monster.second);
        msgpack::pack(data, removedMonsterNickname);
        protocol.addToGeneralData(data);
        map.removeEntity(monster.first);
    }
}

//Itera la lista de players muertos que estan esperando resucitar, aplicando la funcion
//shouldBeRevived y eliminando asi los players que son revividos
void Game::_updateDeadPlayersTimer(ServerProtocol& protocol, double timestep) {
    std::stringstream data;
    ShouldPlayerBeRevived shouldBeRevived(map, data, timestep);
    playersToResurrect.erase(std::remove_if(playersToResurrect.begin(), playersToResurrect.end(), shouldBeRevived),
                             playersToResurrect.end());
    protocol.addToGeneralData(data);
}


/////////////////////////////////PUBLIC//////////////////////////

std::pair<AttackResult, bool> Game::attackPosition(int damage, unsigned int level, bool isAPlayer,
                                    Coordinate coordinate) {
    return map.attackTile(damage, level, isAPlayer, coordinate);
}

void Game::dropItems(std::list<std::shared_ptr<Item>>&& items, Coordinate position) {
    if (items.empty()) {
        throw std::invalid_argument("Received empty list in Game::dropItems");
    }
    mapItems[position] = items.back().get();
    map.addItemsToTile(std::move(items), position);
}

void Game::dropItems(std::shared_ptr<Item> &&item, Coordinate position) {
    if (!item) {
        throw std::invalid_argument("Received null item in Game::dropItems");
    }
    mapItems[position] = item.get();
    map.addItemsToTile(std::move(item), position);
}

void Game::update(double timeStep, ServerProtocol& protocol) {
    _repopulateMap(protocol);
    _updateMonsters(timeStep);
    _updatePlayers(timeStep);
    _executeQueueOperations(protocol);
    _removeMonsters(protocol);
    _updateDeadPlayersTimer(protocol, timeStep);
}

Game::Game(MapFileReader&& mapFile): priests(),  map(mapFile, priests) {
    Configuration& config = Configuration::getInstance();
    monsterCreationRate = config.configMonsterSpawnAmount();
    maxNumberOfMonsters = config.configMaxMonsterAmount();
    spawnInterval = config.configTimeBetweenMonsterSpawns();
    monsterSpawnTimer.start();
}

const Map& Game::getMap() const {
    return map;
}

void Game::list(Player &player, Coordinate coordinate) {
    map.list(player, coordinate);
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

Player& Game::createPlayer(PlayerData& playerData, ServerProtocol& protocol) {
    Coordinate spawnPosition{};
    if (!priests.empty()) {
        spawnPosition = map.getSpawnCoordinateArroundPosition(priests.front());
    } else {
        spawnPosition = map.getSpawnCoordinateArroundPosition(defaultSpawnPoint);
    }
    Banker::addPlayerItems(playerData);
    auto player = std::make_shared<Player>(*this, spawnPosition, playerData);
    Player* playerAux = player.get();
    players.emplace(playerAux->getNickname(), playerAux);
    player->addMessage(WELCOME_MESSAGE);
    map.addEntity(spawnPosition, std::move(player));
    std::stringstream data;
    (*playerAux) >> data;
    protocol.addToGeneralData(data);
    return *playerAux;
}

const std::vector<char>& Game::getCurrentState(ServerProtocol& protocol) {
    return protocol.buildCurrentState(players, monsters,  mapItems);
}

void Game::removePlayer(const std::string& playerNickname, ServerProtocol& protocol) {
    std::stringstream data;
    msgpack::type::tuple<GameType::EventID> eventIdData(GameType::EventID::REMOVE_ENTITY);
    msgpack::pack(data, eventIdData);
    msgpack::type::tuple<std::string>
            removedPlayerNickname(playerNickname);
    msgpack::pack(data, removedPlayerNickname);
    protocol.addToGeneralData(data);
    Coordinate playerPosition = players.at(playerNickname)->getPosition();
    players.erase(playerNickname);
    Banker::erasePlayerItems(playerNickname);
    map.removeEntity(playerPosition);
}

const Item* Game::storeItemFromTileInPlayer(Player& player) {
    Coordinate playerPosition = player.getPosition();
    std::shared_ptr<Item> retreivedItem = map.removeItem(playerPosition);
    const Item* returnData = nullptr;
    if (retreivedItem) {
        if (!player.storeItem(retreivedItem)) {
            returnData = retreivedItem.get();
            map.addItemsToTile(std::move(retreivedItem), playerPosition);
        } else {
            returnData = map.peekShowedItemData(playerPosition);
            if (returnData) {
                mapItems[{playerPosition.iPosition, playerPosition.jPosition}] = returnData;
            } else {
                mapItems.erase({playerPosition.iPosition, playerPosition.jPosition});
            }
        }
    }
    return returnData;
}

bool Game::requestResurrect(Player &player, Coordinate selectedPosition) {
    if (priests.empty() || !player.isDead()) {
        return false;
    }
    Coordinate playerPosition = player.getPosition();
    Coordinate nearestPriest = priests.front();
    for (const auto & priestPosition: priests) {
        if (selectedPosition == priestPosition) {
            player.restoreStats(true);
            return true;
        }
        if (playerPosition.calculateDistance(priestPosition) <
                playerPosition.calculateDistance(nearestPriest)) {
            nearestPriest = priestPosition;
        }
    }
    //Por cada tile de distancia espera 200ms
    auto waitingTime = static_cast<double>(playerPosition.calculateDistance(nearestPriest) * 200);
    player.addMessage(WAITING_TIME_MESSAGE);
    player.addMessage(std::to_string(static_cast<int>(waitingTime/1000)) + " seconds\n");
    playersToResurrect.push_back({waitingTime, 0, nearestPriest, &player});
    return false;
}

void Game::messagePlayer(Player& playerWhoMessaged, const std::string &playerToMessage, const std::string &message) {
    if (players.count(playerToMessage) == 1) {
        Player* player = players.at(playerToMessage);
        player->addMessage(message);
    } else {
        playerWhoMessaged.addMessage(NO_PLAYER_MESSAGE);
    }
}

bool Game::playerExists(const std::string &nickname) const {
    return (players.count(nickname) == 1);
}

void Game::requestRestore(Player& player, Coordinate target) {
    map.requestRestore(player, target);
}

void Game::getPlayerBank(PlayerData &playerData) {
    Banker::getPlayerItems(playerData);
}

bool PlayerShouldBeRemoved::operator()(const Player* player) {
    return (playerToRemove == player);
}
