//
// Created by ivan on 24/6/20.
//

#include "ClientProtocol.h"
#include "GameGUI.h"
#include "Socket.h"
#include <msgpack.hpp>
#include "../Shared/GameEnums.h"
#include "ProtocolEnumTranslator.h"

MSGPACK_ADD_ENUM(GameType::ID)
MSGPACK_ADD_ENUM(GameType::FloorType)
MSGPACK_ADD_ENUM(GameType::Structure)
MSGPACK_ADD_ENUM(GameType::Entity)
MSGPACK_ADD_ENUM(GameType::Weapon)
MSGPACK_ADD_ENUM(GameType::Clothing)
MSGPACK_ADD_ENUM(GameType::Potion)
MSGPACK_ADD_ENUM(GameType::ItemType)

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
    while (offset < msgLength) {
        handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
        msgpack::type::tuple<GameType::ID> id;
        handler->convert(id);
        if (std::get<0>(id) == GameType::ITEM) {
            _processAddItem(handler, offset);
        } else if (std::get<0>(id) == GameType::ENTITY) {
            _processAddEntity(handler, offset);
        }
    }
}

ClientProtocol::ClientProtocol(GameGUI &_game, Socket &_socket) : game(_game), socket(_socket) {
    _receiveMapInfo();
    _receiveCurrentGameState();
}

void ClientProtocol::_processAddItem(msgpack::object_handle &handler, std::size_t& offset) {
    ProtocolEnumTranslator translator;
    TextureID itemTexture = Nothing;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    msgpack::type::tuple<GameType::ItemType, int32_t, uint32_t, uint32_t> itemData;
    handler->convert(itemData);
    GameType::ItemType itemType = std::get<0>(itemData);

    if (itemType == GameType::ITEM_TYPE_WEAPON) {
        itemTexture = translator.getWeaponDropTexture(
                static_cast<GameType::Weapon>(std::get<1>(itemData)));

    } else if (itemType == GameType::ITEM_TYPE_CLOTHING) {
        itemTexture = translator.getClothingDropTexture(
                static_cast<GameType::Clothing>(std::get<1>(itemData)));

    } else if (itemType == GameType::ITEM_TYPE_POTION) {
        itemTexture = translator.getPotionTexture(
                static_cast<GameType::Potion>(std::get<1>(itemData)));
    }
    game.loadTileItem(std::get<2>(itemData), std::get<3>(itemData), itemTexture);
}

void ClientProtocol::_processAddEntity(msgpack::object_handle &handler, std::size_t& offset) {
    ProtocolEnumTranslator translator;
    TextureID itemTexture = Nothing;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    msgpack::type::tuple<GameType::Entity, std::string, uint32_t, uint32_t> entityData;
    handler->convert(entityData);
    if (std::get<0>(entityData) != GameType::PLAYER) {
        game.addEntity(translator.getEntityTexture(std::get<0>(entityData)),
                std::move(std::get<1>(entityData)), std::get<2>(entityData), std::get<3>(entityData));
    } else {

    }
}


