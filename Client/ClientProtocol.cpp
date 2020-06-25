//
// Created by ivan on 24/6/20.
//

#include "ClientProtocol.h"
#include "Socket.h"
#include <vector>
#include <msgpack.hpp>
#include "../Shared/GameEnums.h"
#include "ProtocolEnumTranslator.h"

MSGPACK_ADD_ENUM(GameType::FloorType)
MSGPACK_ADD_ENUM(GameType::Structure)
MSGPACK_ADD_ENUM(GameType::Entity)

void ClientProtocol::receiveMapInfo() {
    uint32_t msgLength;
    socket.receive((char*)(&msgLength), sizeof(msgLength));
    msgLength = ntohl(msgLength);
    std::vector<char> mapInfo(msgLength);
    socket.receive(mapInfo.data(), mapInfo.size());
    std::string str(mapInfo.begin(), mapInfo.end());
    std::size_t offset = 0;
    msgpack::object_handle handler = msgpack::unpack(str.data(), str.size(), offset);
    msgpack::type::tuple<int32_t, int32_t> mapSize;
    handler->convert(mapSize);
    int rows = std::get<0>(mapSize);
    int columns = std::get<1>(mapSize);
    game.setMapSize(rows, columns);
    ProtocolEnumTranslator test;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            handler = msgpack::unpack(str.data(), str.size(), offset);
            msgpack::type::tuple<GameType::FloorType, GameType::Structure, GameType::Entity> tileInfo;
            handler->convert(tileInfo);
            game.loadTileData(i, j, test.getFloorTypeTexture(std::get<0>(tileInfo)),
                    test.getStructureTexture(std::get<1>(tileInfo)),
                    test.getEntityTexture(std::get<2>(tileInfo)));
        }
    }
    while (1) {
        game.render();
    }
}
