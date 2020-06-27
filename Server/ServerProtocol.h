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
    std::unordered_map<std::string, std::vector<char>> playersData; //(nickname, data)

public:
    void operator<<(const Map &map);
    const std::vector<char>& getMapInfo() const;
    std::vector<char> getCurrentState();
};


#endif //ARGENTUM_SERVERPROTOCOL_H
