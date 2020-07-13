//
// Created by ivan on 9/7/20.
//

#include "DropCommand.h"

MSGPACK_ADD_ENUM(GameType::PlayerEvent)

void DropCommand::operator()(std::stringstream &msgBuffer) {
    msgpack::type::tuple<GameType::PlayerEvent> event(GameType::PLAYER_DROP);
    msgpack::type::tuple<int32_t> inventorySlot;
    inventorySlot = slot;
    msgpack::pack(msgBuffer, event);
    msgpack::pack(msgBuffer, inventorySlot);
}
