//
// Created by marcos on 6/29/20.
//
#include <netinet/in.h>
#include "UpdateReceiver.h"
#include "../../libs/Socket.h"
#include "../UpdateEvents/UpdateMove.h"
#include "../UpdateEvents/UpdateCreatePlayer.h"
#include "../UpdateEvents/UpdateCreateNPC.h"
#include "../UpdateEvents/UpdateGUI.h"
#include "../UpdateEvents/UpdateRemoveEntity.h"
#include "../UpdateEvents/UpdateEquip.h"
#include "../UpdateEvents/UpdateCreateItem.h"
#include "../UpdateEvents/UpdatePlayerDeath.h"
#include "../UpdateEvents/UpdateAttack.h"
#include "../UpdateEvents/UpdateDestroyItem.h"
#include "../UpdateEvents/UpdateTeleportEntity.h"
#include "../UpdateEvents/UpdatePlayerResurrect.h"

MSGPACK_ADD_ENUM(GameType::EventID)
MSGPACK_ADD_ENUM(GameType::Direction)
MSGPACK_ADD_ENUM(GameType::Entity)
MSGPACK_ADD_ENUM(GameType::EquipmentPlace)
MSGPACK_ADD_ENUM(GameType::ItemType)
MSGPACK_ADD_ENUM(GameType::Weapon)

void UpdateReceiver::run() {
    try {
        uint32_t msgLength = 0;
        while (!quit) {
            offset = 0;
            socket.receive((char *) (&msgLength), sizeof(uint32_t));
            msgLength = ntohl(msgLength);
            buffer.clear();
            buffer.resize(msgLength);
            socket.receive(buffer.data(), msgLength);
            _processUpdate(msgLength);
            updates.deliverUpdate();
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unkown error in UpdateReceiver" << std::endl;
    }
    quit = true;
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
                _processAttack();
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
                _processCreateItem();
                break;
            case GameType::REMOVE_ENTITY:
                _processRemoveEntity();
                break;
            case GameType::PLAYER_DEATH:
                _processPlayerDeath();
                break;
            case GameType::DESTROY_ITEM:
                _processDestroyItem();
                break;
            case GameType::TELEPORTED:
                _processTeleportEntity();
                break;
            case GameType::RESURRECTED:
                _processPlayerResurrect();
                break;
            default:
                std::cerr << std::get<0>(id) << " comando no reconocido" << std::endl;
                break;
        }
    }
    _receivePlayerData();
}

void UpdateReceiver::_processTeleportEntity() {
    msgpack::type::tuple<std::string, int32_t, int32_t> teleportData;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(teleportData);
    updates.push(std::unique_ptr<UpdateEvent>(new UpdateTeleportEntity(
                            std::move(std::get<0>(teleportData)),
                                    {std::get<1>(teleportData),
                                    std::get<2>(teleportData)})));
}

void UpdateReceiver::_processDestroyItem() {
    msgpack::type::tuple<int32_t, int32_t> itemPosition;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(itemPosition);
    updates.push(std::unique_ptr<UpdateEvent>(new UpdateDestroyItem({std::get<0>(itemPosition),
                                                std::get<1>(itemPosition)})));
}

void UpdateReceiver::_processAttack() {
    msgpack::type::tuple<std::string, int32_t, int32_t, GameType::Weapon,
                                                GameType::Direction> entity;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(entity);
    updates.push(std::unique_ptr<UpdateEvent>(
            new UpdateAttack(std::get<0>(entity),
                             {std::get<1>(entity), std::get<2>(entity)},
                    std::get<3>(entity), std::get<4>(entity))));
}


void UpdateReceiver::_processPlayerDeath() {
    msgpack::type::tuple<std::string> player;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(player);
    updates.push(std::unique_ptr<UpdateEvent>(
            new UpdatePlayerDeath(std::move(std::get<0>(player)))));
}

void UpdateReceiver::_processPlayerResurrect() {
    msgpack::type::tuple<std::string> player;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(player);
    updates.push(std::unique_ptr<UpdateEvent>(new UpdatePlayerResurrect(
                                            std::move(std::get<0>(player)))));
}

void UpdateReceiver::_processCreateItem() {
    msgpack::type::tuple<GameType::ItemType, int32_t, int32_t, int32_t> itemData;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(itemData);
    updates.push(std::unique_ptr<UpdateEvent>(new UpdateCreateItem(std::get<0>(itemData),
                std::get<1>(itemData), {std::get<2>(itemData), std::get<3>(itemData)})));
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
