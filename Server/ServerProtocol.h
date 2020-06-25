//
// Created by marcos on 6/24/20.
//

#ifndef ARGENTUM_SERVERPROTOCOL_H
#define ARGENTUM_SERVERPROTOCOL_H


#include "../Map/Map.h"
#include <msgpack.hpp>
#include <sstream>

class ServerProtocol {
private:
    std::stringstream mapBuffer;

public:
    void operator<<(const Map &map);
};


#endif //ARGENTUM_SERVERPROTOCOL_H
