//
// Created by marcos on 6/29/20.
//

#include <netinet/in.h>
#include "UpdateReceiver.h"
#include "Socket.h"
#include "../Shared/GameEnums.h"
#include "../UpdateEvents/UpdateMove.h"

MSGPACK_ADD_ENUM(GameType::EventID)
MSGPACK_ADD_ENUM(GameType::Direction)

void UpdateReceiver::run() {
    uint32_t msgLength = 0;
    while (!quit) {
        try {
            offset = 0;
            socket.receive((char*)(&msgLength), sizeof(uint32_t));
            msgLength = ntohl(msgLength);
            buffer.resize(msgLength);
            buffer.clear();
            socket.receive(buffer.data(), msgLength);
            _processUpdate();
            updates.deliverUpdate();
        } catch (...) {
            //do nothing
        }
    }
}

void UpdateReceiver::_processUpdate() {
    msgpack::type::tuple<GameType::EventID> id;
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
    }
}

void UpdateReceiver::_processMoveUpdate() {
    msgpack::type::tuple<GameType::Direction, int32_t, std::string, bool> moveInfo;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(moveInfo);
    updates.push(std::unique_ptr<UpdateEvent>(new UpdateMove(std::move(std::get<2>(moveInfo)),
            std::get<0>(moveInfo), std::get<1>(moveInfo), std::get<3>(moveInfo))));
}
