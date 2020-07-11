//
// Created by marcos on 6/24/20.
//

#include "ServerProtocol.h"
#include <iostream>
#include "../Entities/PlayerProxy.h"
#include "../Entities/Player.h"
#include "../Entities/Monster.h"
#include "../Game/Game.h"
#include "../Items/ItemData.h"

#include <msgpack.hpp>

MSGPACK_ADD_ENUM(GameType::EventID)
MSGPACK_ADD_ENUM(GameType::ItemType)



///////////////////////////////PUBLIC/////////////////////////////

ServerProtocol::ServerProtocol(const Game& _game): game(_game) {
    std::stringstream aux;
    game.getMap() >> aux;
    uint32_t msgLength = aux.str().size();
    msgLength = htonl(msgLength); /*Enviamos la longitud en big endian 4 bytes*/
    mapBuffer.resize(sizeof(uint32_t));
    _loadBytes(mapBuffer, &msgLength, sizeof(uint32_t));
    std::string auxStr = aux.str();
    std::copy(auxStr.begin(), auxStr.end(), std::back_inserter(mapBuffer));
}

const std::vector<char> &ServerProtocol::getMapInfo() const {
    return mapBuffer;
}

const std::vector<char>& ServerProtocol::buildCurrentState(
                                          const std::unordered_map<std::string, Player*>& players,
                                          //const std::list<Player*>& players,
                                          const std::list<Monster*>& monsters,
                                          const std::unordered_map<Coordinate, const Item*>& mapItems) {
    std::stringstream data;
    for (const auto & player : players) {
        (*player.second) >> data;
    }
    for (const auto & monster : monsters) {
        (*monster) >> data;
    }
    for (const auto & item : mapItems) {
        /*
        msgpack::type::tuple<GameType::EventID> eventIdData(GameType::CREATE_ITEM);
        msgpack::pack(data, eventIdData);
        msgpack::type::tuple<GameType::ItemType, int32_t, int32_t, int32_t>
                itemDataTuple(itemData.second.type, itemData.second.id, itemData.second.coordinate.iPosition,
                              itemData.second.coordinate.jPosition);
        msgpack::pack(data, itemDataTuple);
        */
        item.second->loadDropItemData(data, item.first.iPosition, item.first.jPosition);
    }
    std::string auxString = data.str();
    uint32_t msgLength = htonl(auxString.size());
    currentStateBuffer.resize(sizeof(uint32_t));
    _loadBytes(currentStateBuffer, &msgLength, sizeof(uint32_t));
    std::copy(auxString.begin(), auxString.end(), std::back_inserter(currentStateBuffer));
    return currentStateBuffer;
}

void ServerProtocol::addToGeneralData(std::stringstream &data) {
    generalData << data.str();
}

const std::vector<char>& ServerProtocol::getGeneralData() {
    return generalDataBuffer;
}

void ServerProtocol::buildGeneralDataBuffer() {
    std::string auxString = generalData.str();
    uint32_t msgLength = htonl(auxString.size());
    generalDataBuffer.resize(sizeof(uint32_t));
    _loadBytes(generalDataBuffer, &msgLength, sizeof(uint32_t));
    std::copy(auxString.begin(), auxString.end(), std::back_inserter(generalDataBuffer));
    generalData.str("");
    generalData.clear();
}

std::vector<char> ServerProtocol::getPlayerData(PlayerProxy& player) {
    std::stringstream data;
    player.storeAllRelevantData(data);
    player.clearMinichat();
    std::string auxString = data.str();
    uint32_t msgLength = htonl(auxString.size());
    std::vector<char> buffer(sizeof(uint32_t));
    _loadBytes(buffer, &msgLength, sizeof(uint32_t));
    std::copy(auxString.begin(), auxString.end(), std::back_inserter(buffer));
    return buffer;
}

///////////////////////////////PRIVATE/////////////////////////////

void ServerProtocol::_loadBytes(std::vector<char>& buffer, void* data, unsigned int size) {
    for (unsigned int i = 0; i < size; ++i) {
        buffer[i] = *(reinterpret_cast<char *>(data) + i);
    }
}
