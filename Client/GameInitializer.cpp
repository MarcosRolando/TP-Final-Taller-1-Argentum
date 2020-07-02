//
// Created by marcos on 7/1/20.
//

#include "GameInitializer.h"
#include <cstdint>
#include "Socket.h"
#include <msgpack.hpp>
#include "../Shared/GameEnums.h"
#include "GameGUI.h"
#include "ProtocolEnumTranslator.h"
#include "ClientProtocol.h"

void GameInitializer::initializeGame() {
    _receiveMapInfo();
    _receiveCurrentGameState();
}

void GameInitializer::_receiveMapInfo() {
    int32_t msgLength;
    socket.receive((char*)(&msgLength), sizeof(msgLength));
    msgLength = ntohl(msgLength);
    std::vector<char> buffer(msgLength);
    socket.receive(buffer.data(), buffer.size());
    _loadMap(buffer);
}

void GameInitializer::_receiveCurrentGameState() {
    int32_t msgLength;
    socket.receive((char*)(&msgLength), sizeof(msgLength));
    msgLength = ntohl(msgLength);
    std::vector<char> buffer(msgLength);
    socket.receive(buffer.data(), msgLength);
    std::size_t offset = 0;
    msgpack::object_handle handler;

    while (offset < static_cast<size_t>(msgLength)) {
        handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
        msgpack::type::tuple<GameType::EventID> id;
        handler->convert(id);
        if (std::get<0>(id) == GameType::CREATE_ITEM) {
            ItemData data = protocol.processAddItem(offset);
            game.loadTileItem(data.position, data.texture);
        } else if (std::get<0>(id) == GameType::CREATE_ENTITY) {
            protocol.processAddEntity(offset);
        } else if (std::get<0>(id) == GameType::PLAYER_DATA) { /*Esto es el inventario y stats*/
            PlayerData data = protocol.processAddPlayerData(offset);
            //todo llamar al game con los datos recibidos
        }
    }
}


void GameInitializer::_loadMap(std::vector<char>& buffer) {
    std::size_t offset = 0;
    msgpack::object_handle handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    msgpack::type::tuple<int32_t, int32_t> mapSize;
    ProtocolEnumTranslator translator;
    handler->convert(mapSize);
    int rows = std::get<0>(mapSize);
    int columns = std::get<1>(mapSize);
    game.setMapSize(rows, columns);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
            msgpack::type::tuple<GameType::FloorType, GameType::Structure, GameType::Entity> tileInfo;
            handler->convert(tileInfo);
            game.loadTileData({i, j}, translator.getFloorTypeTexture(std::get<0>(tileInfo)),
                              translator.getStructureTexture(std::get<1>(tileInfo)),
                              translator.getEntityTexture(std::get<2>(tileInfo)));
        }
    }
}

void GameInitializer::loadPlayer(const std::string& nickname, GameType::Race race,
                                  GameType::Class _class) {
    std::stringstream msgBuffer;
    msgpack::type::tuple<GameType::PlayerEvent> event(GameType::CREATE_PLAYER);
    msgpack::type::tuple<std::string, GameType::Race, GameType::Class> playerInfo;
    playerInfo = {nickname, race, _class};
    msgpack::pack(msgBuffer, event);
    msgpack::pack(msgBuffer, playerInfo);
    std::string aux = msgBuffer.str();
    uint32_t length = aux.size();
    length = htonl(aux.size());
    std::vector<char> sendBuffer(sizeof(uint32_t));
    ClientProtocol::loadBytes(sendBuffer, &length, sizeof(uint32_t));
    std::copy(aux.begin(), aux.end(), std::back_inserter(sendBuffer));
    socket.send(sendBuffer.data(), sendBuffer.size());
}


void GameInitializer::loadPlayer(std::string& nickname) {
    std::stringstream msgBuffer;
    msgpack::type::tuple<GameType::PlayerEvent> event(GameType::CREATE_PLAYER);
    msgpack::type::tuple<std::string> playerInfo;
    playerInfo = {nickname};
    msgpack::pack(msgBuffer, event);
    msgpack::pack(msgBuffer, playerInfo);
    std::string aux = msgBuffer.str();
    uint32_t length = aux.size();
    length = htonl(aux.size());
    std::vector<char> sendBuffer(sizeof(uint32_t));
    ClientProtocol::loadBytes(sendBuffer, &length, sizeof(uint32_t));
    std::copy(aux.begin(), aux.end(), std::back_inserter(sendBuffer));
    socket.send(sendBuffer.data(), sendBuffer.size());
}

