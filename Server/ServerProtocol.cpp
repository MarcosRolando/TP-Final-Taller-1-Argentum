//
// Created by marcos on 6/24/20.
//

#include "ServerProtocol.h"
#include <iostream>
#include "../Entities/PlayerProxy.h"
#include "../Entities/Player.h"

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

std::vector<char> ServerProtocol::getCurrentState(PlayerProxy& proxyPlayer) {
    const Player& player = proxyPlayer.getPlayer();
    std::vector<char> buffer;
    std::stringstream data;
    map.getCurrentState(data);
    player.storeAllRelevantData(data);
    std::string auxString = data.str();
    uint32_t msgLength = htonl(auxString.size());
    buffer.resize(sizeof(uint32_t));
    _loadBytes(buffer, &msgLength, sizeof(uint32_t));
    std::copy(auxString.begin(), auxString.end(), std::back_inserter(buffer));
    return buffer;
}

void ServerProtocol::addToGeneralData(std::stringstream &data) {
    generalData << data.str();
}

const std::vector<char>& ServerProtocol::getGeneralData(std::vector<char>& length) {
    return generalDataBuffer;
}

void ServerProtocol::buildGeneralDataBuffer() {
    std::string auxString = generalData.str();
    uint32_t msgLength = htonl(auxString.size());
    generalDataBuffer.resize(sizeof(uint32_t));
    _loadBytes(generalDataBuffer, &msgLength, sizeof(uint32_t));
    std::copy(auxString.begin(), auxString.end(), std::back_inserter(generalDataBuffer));
    generalData.clear();
}

///////////////////////////////PRIVATE/////////////////////////////

void ServerProtocol::_loadBytes(std::vector<char>& buffer, void* data, unsigned int size) {
    for (unsigned int i = 0; i < size; ++i) {
        buffer[i] = *(reinterpret_cast<char *>(data) + i);
    }
}