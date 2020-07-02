//
// Created by marcos on 6/29/20.
//

#include <netinet/in.h>
#include "UpdateReceiver.h"
#include "Socket.h"
#include "../UpdateEvents/UpdateMove.h"

MSGPACK_ADD_ENUM(GameType::EventID)
MSGPACK_ADD_ENUM(GameType::Direction)
MSGPACK_ADD_ENUM(GameType::Entity)

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
                break;
            case GameType::UNEQUIP:
                break;
            case GameType::USE_ITEM:
                break;
            case GameType::CREATE_ENTITY:
                _processCreateEntity();
                break;
            case GameType::CREATE_ITEM:
                break;
            default:
                break;
        }
    }
}

void UpdateReceiver::_processMoveUpdate() {
    msgpack::type::tuple<GameType::Direction, int32_t, std::string, bool> moveInfo;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(moveInfo);
    updates.push(std::unique_ptr<UpdateEvent>(new UpdateMove(std::move(std::get<2>(moveInfo)),
            std::get<0>(moveInfo), std::get<1>(moveInfo), std::get<3>(moveInfo))));
}

void UpdateReceiver::_processCreateEntity() {
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    msgpack::type::tuple<GameType::Entity, std::string, int32_t , int32_t> entityData;
    handler->convert(entityData);
    if (std::get<0>(entityData) != GameType::PLAYER) {
        EntityData data = protocol.processAddNPC(entityData, offset);
        //game.addNPC(data.texture, std::move(data.nickname), data.pos); //todo push backd del evente de creacion
    } else {
        MapPlayerData data = protocol.processAddPlayer(entityData, offset);
        //game.addPlayer(data.equipment, data.isAlive,
                       //std::move(data.entityData.nickname), data.entityData.pos);
    }
}
