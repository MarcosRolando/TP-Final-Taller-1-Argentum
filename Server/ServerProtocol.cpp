//
// Created by marcos on 6/24/20.
//

#include "ServerProtocol.h"
#include <iostream>

void ServerProtocol::operator<<(const Map &map) {
    std::stringstream aux;
    map >> aux;
    uint32_t msgLength = aux.str().size();
    msgLength = htonl(msgLength); /*Enviamos la longitud en big endian 4 bytes*/
    mapBuffer.resize(sizeof(uint32_t));
    for (int i = 0; i < sizeof(uint32_t); ++i) {
        mapBuffer[i] = *(reinterpret_cast<char *>(&msgLength) + i);
    }
    std::string auxStr = aux.str();
    std::copy(auxStr.begin(), auxStr.end(), std::back_inserter(mapBuffer));
}

const std::vector<char> &ServerProtocol::getMapInfo() const {
    return mapBuffer;
}
