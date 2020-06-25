//
// Created by marcos on 6/24/20.
//

#ifndef ARGENTUM_SERVERPROTOCOL_H
#define ARGENTUM_SERVERPROTOCOL_H


#include "../Map/Map.h"
#include <msgpack.hpp>

class ServerProtocol {
private:
    std::vector<char> mapBuffer;

public:
    void operator<<(const Map &map);
};


#endif //ARGENTUM_SERVERPROTOCOL_H
