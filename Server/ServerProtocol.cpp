//
// Created by marcos on 6/24/20.
//

#include "ServerProtocol.h"

void ServerProtocol::operator<<(const Map &map) {
    map >> mapBuffer;
}