//
// Created by marcos on 7/1/20.
//

#include "GameInitializer.h"
#include <cstdint>
#include "../../libs/Socket.h"
#include <msgpack.hpp>
#include "GameGUI.h"
#include "ProtocolEnumTranslator.h"
#include "ClientProtocol.h"
#include "CitizenData.h"

MSGPACK_ADD_ENUM(GameType::PlayerEvent)
MSGPACK_ADD_ENUM(GameType::EventID)
MSGPACK_ADD_ENUM(GameType::Race)
MSGPACK_ADD_ENUM(GameType::Class)
MSGPACK_ADD_ENUM(GameType::Entity)
MSGPACK_ADD_ENUM(GameType::Structure)
MSGPACK_ADD_ENUM(GameType::FloorType)

void GameInitializer::initializeGame() {
    _receiveMapInfo();
    _receiveCurrentGameState();
}

/* Recibe la informacion del mapa */
void GameInitializer::_receiveMapInfo() {
    int32_t msgLength;
    socket.receive((char*)(&msgLength), sizeof(msgLength));
    msgLength = ntohl(msgLength);
    std::vector<char> buffer(msgLength);
    socket.receive(buffer.data(), buffer.size());
    _loadMap(buffer);
}

/* Recibe el estado inicial del juego */
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
            ItemData data = protocol.processAddItem(&buffer, offset);
            game.createItem(data.position, data.texture);
        } else if (std::get<0>(id) == GameType::CREATE_ENTITY) {
            _processAddEntity(buffer, offset);
        }
    }
    game.getMap().update();
    _receivePlayerData();
}

/* Procesa la entidad que recibe del server y la agrega al juego */
void GameInitializer::_processAddEntity(std::vector<char>& buffer, std::size_t& offset) {
    msgpack::object_handle handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    msgpack::type::tuple<GameType::Entity, std::string, int32_t> entityData;
    handler->convert(entityData);
    if (std::get<0>(entityData) != GameType::PLAYER) {
        EntityData data = protocol.processAddNPC(&buffer, entityData, offset);
        game.addNPC(data);
    } else {
        MapPlayerData data = protocol.processAddPlayer(&buffer, entityData, offset);
        game.addPlayer(data);
    }
}

/* Carga las texturas de cada tile del mapa*/
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
            msgpack::type::tuple<GameType::FloorType, GameType::Structure,
            GameType::Entity, std::string> tileInfo;
            handler->convert(tileInfo);
            CitizenData citizen = {translator.getEntityTexture(std::get<2>(tileInfo)),
                                   std::get<3>(tileInfo)};
            game.loadTileData({i, j}, translator.getFloorTypeTexture(std::get<0>(tileInfo)),
                              translator.getStructureTexture(std::get<1>(tileInfo)),
                              citizen);
        }
    }
}

void GameInitializer::createPlayer(const std::string& nickname, GameType::Race race,
                                   GameType::Class _class) {
    game.getMap().setPlayerNickname(nickname);//Para despues poder buscar la posicion del player en Map
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

void GameInitializer::loadPlayer(const std::string& nickname) {
    game.getMap().setPlayerNickname(nickname);//Para despues poder buscar la posicion del player en Map
    std::stringstream msgBuffer;
    msgpack::type::tuple<GameType::PlayerEvent> event(GameType::LOAD_PLAYER);
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

/* Recibe toda la informacion inicial del jugador */
void GameInitializer::_receivePlayerData() {
    uint32_t length = 0;
    socket.receive(reinterpret_cast<char*>(&length), sizeof(uint32_t));
    length = ntohl(length);
    std::vector<char> buffer(length);
    socket.receive(buffer.data(), length);
    PlayerData data = protocol.processAddPlayerData(&buffer);
    game.getPlayerInventory().updateGold(data.generalInfo.gold, data.generalInfo.safeGold);
    for (const auto & item : data.equippedItems) {
        game.getPlayerInventory().addEquipableItem(std::get<0>(item),
                                                   std::get<1>(item));
    }
    for (const auto & item : data.inventoryItems) {
        game.getPlayerInventory().addInventoryItem(std::get<0>(item),
                                                   std::get<1>(item));
    }
    game.setCameraOn(data.generalInfo.nickname);
    game.getPlayerInfo().update(data.generalInfo);
    game.getMinichat().receiveText(data.minichatText);
}

