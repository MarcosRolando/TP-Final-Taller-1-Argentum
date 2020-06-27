//
// Created by ivan on 24/6/20.
//

#include "ClientProtocol.h"
#include "GameGUI.h"
#include "Socket.h"
#include <msgpack.hpp>
#include "../Shared/GameEnums.h"
#include "ProtocolEnumTranslator.h"

MSGPACK_ADD_ENUM(GameType::FloorType)
MSGPACK_ADD_ENUM(GameType::Structure)
MSGPACK_ADD_ENUM(GameType::Entity)

void ClientProtocol::_loadMap() {
    std::size_t offset = 0;
    msgpack::object_handle handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    msgpack::type::tuple<int32_t, int32_t> mapSize;
    handler->convert(mapSize);
    int rows = std::get<0>(mapSize);
    int columns = std::get<1>(mapSize);
    game.setMapSize(rows, columns);
    ProtocolEnumTranslator translator;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
            msgpack::type::tuple<GameType::FloorType, GameType::Structure, GameType::Entity> tileInfo;
            handler->convert(tileInfo);
            game.loadTileData(i, j, translator.getFloorTypeTexture(std::get<0>(tileInfo)),
                              translator.getStructureTexture(std::get<1>(tileInfo)),
                              translator.getEntityTexture(std::get<2>(tileInfo)));
        }
    }
}

void ClientProtocol::_receiveMapInfo() {
    uint32_t msgLength;
    socket.receive((char*)(&msgLength), sizeof(msgLength));
    msgLength = ntohl(msgLength);
    buffer.resize(msgLength);
    socket.receive(buffer.data(), buffer.size());
    _loadMap();
}

void ClientProtocol::_receiveCurrentGameState() {
    uint32_t msgLength;
    socket.receive((char*)(&msgLength), sizeof(msgLength));
    msgLength = ntohl(msgLength);
    buffer.resize(msgLength);
    socket.receive(buffer.data(), msgLength);
    std::size_t offset = 0;
    msgpack::object_handle handler = msgpack::unpack(buffer.data(), buffer.size(), offset);

}

ClientProtocol::ClientProtocol(GameGUI &_game, Socket &_socket) : game(_game), socket(_socket) {
    _receiveMapInfo();
    _receiveCurrentGameState();
}


