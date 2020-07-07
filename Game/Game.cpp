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
#include "../Server/InitialPlayerData.h"

MSGPACK_ADD_ENUM(GameType::EventID)

/////////////////////////////////PRIVATE//////////////////////////


//Carga hasta monsterCreationRate monstruos nuevos cada cierto invervalo de tiempo
//Si la cantidad que se desea crear sobrepasa la cantidad maxima, entonces crea hasta
//conseguir la cantidad maxima
void Game::_repopulateMap(double timePassed, ServerProtocol& protocol) {
    Coordinate aux{};
    std::stringstream data;
    spawnTimer += static_cast<unsigned int>(timePassed);
    if (spawnTimer >= spawnInterval) {
        unsigned int monstersToCreate = monsterCreationRate;
        std::shared_ptr<Monster> monster;
        spawnTimer = 0;
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
        player.second->update(timeStep);
    }
}

//Elimina de las listas almacenadas y del mapa los players y monsters que deban ser eliminados
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

/////////////////////////////////PUBLIC//////////////////////////

AttackResult Game::attackPosition(int damage, unsigned int level, bool isAPlayer,
                                    Coordinate coordinate) {
    return map.attackTile(damage, level, isAPlayer, coordinate);
}

void Game::dropItems(std::list<std::shared_ptr<Item>>&& items, Coordinate position) {
    if (items.empty()) {
        throw std::invalid_argument("Received empty list in Game::dropItems");
    }
    //mapItems[position] = {items.back()->getType(), items.back()->getId(), position};
    mapItems[position] = items.back().get();
    map.addItemsToTile(std::move(items), position);
}

void Game::dropItems(std::shared_ptr<Item> &&item, Coordinate position) {
    if (!item) {
        throw std::invalid_argument("Received null item in Game::dropItems");
    }
    //mapItems[position] = {item->getType(), item->getId(), position};
    mapItems[position] = item.get();
    map.addItemsToTile(std::move(item), position);
}

void Game::update(double timeStep, ServerProtocol& protocol) {
    _repopulateMap(timeStep, protocol);
    _updateMonsters(timeStep);
    _updatePlayers(timeStep);
    _executeQueueOperations(protocol);

    //AGREGAR UPDATE DE PLAYERS CONECTADOS (no hay que borrar esto????)

    _removeMonsters(protocol);
}

Game::Game(MapFileReader&& mapFile): map(mapFile) {
    monsterCreationRate = 20;
    maxNumberOfMonsters = 300;
    spawnInterval = 100;
    spawnTimer = 0;
}

const Map& Game::getMap() const {
    return map;
}

/*
unsigned int Game::list(Player &player, std::list<ProductData> &products, Coordinate coordinate) {
    return map.list(player, products, coordinate);
}
*/

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

/*
Game::Game(ClientsMonitor&& clientAux //= ClientsMonitor()): clients(clientAux) {

}
*/
#include "../Items/Attack/Weapon.h"
#include "../Items/Defense/Head.h"
#include "../Items/Defense/Shield.h"

Player& Game::createPlayer(InitialPlayerData& playerData, ServerProtocol& protocol) {
    //todo ver si lo spawneamos en un area especifica tipo la capital o pueblos
    int x = 0;
    Coordinate position{};
    while (true) { //esto es solo por ahora para generar al player en el primer tile disponible
        position = {0, x};
        if (map.isPlaceAvailable(position)) break;
        ++x;
    }
    std::shared_ptr<Player> player(new Player(*this, playerData.race, playerData._class, 1,
                                0, position, std::move(playerData.nickname)));
    std::shared_ptr<Item> item(new Weapon(GameType::LONGSWORD));
    player->storeItem(item);
    item.reset(new Weapon(GameType::GNARLED_STAFF));
    player->storeItem(item);
    item.reset(new Weapon(GameType::GNARLED_STAFF));
    player->storeItem(item);
    item.reset(new Weapon(GameType::LONGSWORD));
    player->storeItem(item);
    item.reset(new Head(GameType::MAGIC_HAT));
    player->storeItem(item);
    item.reset(new Head(GameType::IRON_HELMET));
    player->storeItem(item);
    item.reset(new Shield(GameType::IRON_SHIELD));
    player->storeItem(item);
    player->useItem(0);
    Player* playerAux = player.get();
    players.emplace(&playerAux->getNickname(), playerAux);
    map.addEntity(position, std::move(player));
    std::stringstream data;
    (*playerAux) >> data;
    protocol.addToGeneralData(data);
    return *playerAux;
}

const std::vector<char>& Game::getCurrentState(ServerProtocol& protocol) {
    return protocol.buildCurrentState(players, monsters,  mapItems);
}

void Game::removePlayer(Player *player, ServerProtocol& protocol) {
    std::stringstream data;
    msgpack::type::tuple<GameType::EventID> eventIdData(GameType::EventID::REMOVE_ENTITY);
    msgpack::pack(data, eventIdData);
    msgpack::type::tuple<std::string>
            removedPlayerNickname(player->getNickname());
    msgpack::pack(data, removedPlayerNickname);
    protocol.addToGeneralData(data);
    //PlayerShouldBeRemoved shouldBeRemoved(player);
    //players.erase(std::remove_if(players.begin(), players.end(), shouldBeRemoved),
    //                            players.end());
    players.erase(&player->getNickname());
    map.removeEntity(player->getPosition());
}

//ItemData Game::storeItemFromTileInPlayer(Player& player) {
const Item* Game::storeItemFromTileInPlayer(Player& player) {
    Coordinate playerPosition = player.getPosition();
    std::shared_ptr<Item> retreivedItem = map.removeItem(playerPosition);
    //ItemData returnData = {GameType::ITEM_TYPE_NONE, -2, playerPosition};
    const Item* returnData = nullptr;
    if (retreivedItem) {
        if (!player.storeItem(retreivedItem)) {
            map.addItemsToTile(std::move(retreivedItem), playerPosition);
        } else {
            //std::pair<GameType::ItemType, int32_t> showedItem = map.peekShowedItemData(playerPosition);
            returnData = map.peekShowedItemData(playerPosition);
            if (returnData) {
                mapItems[{playerPosition.iPosition, playerPosition.jPosition}] = returnData;
                //return {showedItem.first, showedItem.second, playerPosition};
            } else {
                mapItems.erase({playerPosition.iPosition, playerPosition.jPosition});
            }
        }
    }
    return returnData;
}

bool PlayerShouldBeRemoved::operator()(const Player* player) {
    return (playerToRemove == player);
}
