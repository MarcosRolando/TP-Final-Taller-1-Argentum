//
// Created by marcos on 6/29/20.
//

#include <netinet/in.h>
#include "UpdateReceiver.h"
#include "Socket.h"
#include "../UpdateEvents/UpdateMove.h"
#include "../UpdateEvents/UpdateCreatePlayer.h"
#include "../UpdateEvents/UpdateCreateNPC.h"
#include "../UpdateEvents/UpdateGUI.h"
#include "../UpdateEvents/UpdateRemoveEntity.h"
#include "../UpdateEvents/UpdateEquip.h"

MSGPACK_ADD_ENUM(GameType::EventID)
MSGPACK_ADD_ENUM(GameType::Direction)
MSGPACK_ADD_ENUM(GameType::Entity)
MSGPACK_ADD_ENUM(GameType::EquipmentPlace)

void UpdateReceiver::run() {
    uint32_t msgLength = 0;
    while (!quit) {
        try {
            offset = 0;
            socket.receive((char*)(&msgLength), sizeof(uint32_t));
            msgLength = ntohl(msgLength);
            buffer.clear();
            buffer.resize(msgLength);
            socket.receive(buffer.data(), msgLength);
            _processUpdate(msgLength);
            updates.deliverUpdate();
        } catch (...) {
            //do nothing
        }
    }
}

void UpdateReceiver::_processUpdate(uint32_t msgLength) {
    msgpack::type::tuple<GameType::EventID> id;
    while (offset < msgLength) {
        handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
        handler->convert(id);
        switch (std::get<0>(id)) {
            case GameType::MOVED:
                _processMoveUpdate();
                break;
            case GameType::ATTACK:
                handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
                break;
            case GameType::UNEQUIP:
                _processUnequip();
                break;
            case GameType::EQUIPPED:
                _processEquipped();
                break;
            case GameType::CREATE_ENTITY:
                _processCreateEntity();
                break;
            case GameType::CREATE_ITEM:
                break;
            case GameType::REMOVE_ENTITY:
                _processRemoveEntity();
                break;
            default:
                break;
        }
    }
    _receivePlayerData();
}

void UpdateReceiver::_processUnequip() {
    msgpack::type::tuple<std::string, GameType::EquipmentPlace> data;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(data);
    updates.push(std::unique_ptr<UpdateEvent>(new UpdateEquip(std::move(std::get<0>(data)),
                                    std::get<1>(data), UNEQUIP)));
}

void UpdateReceiver::_processEquipped() {
    msgpack::type::tuple<std::string, GameType::EquipmentPlace, int32_t> data;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(data);
    updates.push(std::unique_ptr<UpdateEvent>(new UpdateEquip(std::move(std::get<0>(data)),
                std::get<1>(data), std::get<2>(data))));
}

void UpdateReceiver::_processMoveUpdate() {
    msgpack::type::tuple<GameType::Direction, int32_t, std::string, bool> moveInfo;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(moveInfo);
    updates.push(std::unique_ptr<UpdateEvent>(new UpdateMove(std::move(std::get<2>(moveInfo)),
            std::get<0>(moveInfo), std::get<1>(moveInfo), std::get<3>(moveInfo))));
}

void UpdateReceiver::_processRemoveEntity() {
    msgpack::type::tuple<std::string> nickname;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(nickname);
    updates.push(std::unique_ptr<UpdateEvent>(new UpdateRemoveEntity(
                                        std::move(std::get<0>(nickname)))));
}

void UpdateReceiver::_processCreateEntity() {
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    msgpack::type::tuple<GameType::Entity, std::string> entityData;
    handler->convert(entityData);
    if (std::get<0>(entityData) != GameType::PLAYER) {
        EntityData data = protocol.processAddNPC(&buffer, entityData, offset);
        updates.push(std::unique_ptr<UpdateEvent>(new UpdateCreateNPC(data)));
    } else {
        MapPlayerData data = protocol.processAddPlayer(&buffer, entityData, offset);
        updates.push(std::unique_ptr<UpdateEvent>(new UpdateCreatePlayer(data)));
    }
}

void UpdateReceiver::_receivePlayerData() {
    uint32_t length = 0;
    socket.receive(reinterpret_cast<char*>(&length), sizeof(uint32_t));
    length = ntohl(length);
    buffer.clear();
    buffer.resize(length);
    socket.receive(buffer.data(), length);
    PlayerData data = protocol.processAddPlayerData(&buffer);
    updates.push(std::unique_ptr<UpdateEvent>(new UpdateGUI(std::move(data))));
}
