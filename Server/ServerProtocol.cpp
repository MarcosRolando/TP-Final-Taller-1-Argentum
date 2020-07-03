//
// Created by marcos on 6/24/20.
//

#include "ServerProtocol.h"
#include <iostream>
#include "../Entities/PlayerProxy.h"
#include "../Entities/Player.h"
#include "../Entities/Entity.h"
#include "../Entities/Monster.h"

///////////////////////////////PUBLIC/////////////////////////////

ServerProtocol::ServerProtocol(const Map &map): map(map) {
    std::stringstream aux;
    map >> aux;
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

const std::vector<char>& ServerProtocol::buildCurrentState(const std::list<Player*>& players,
                                                    const std::list<Monster*>& monsters) {
    std::stringstream data;
    for (const auto & player : players) {
        (*player) >> data;
    }
    for (const auto & monster : monsters) {
        (*monster) >> data;
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

std::vector<char> ServerProtocol::getPlayerData(const PlayerProxy& player) {
    std::stringstream data;
    player.storeAllRelevantData(data);
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

void ServerProtocol::storeEntityInitialData(const Entity *entity) {
    (*entity) >> currentStateData;
}
