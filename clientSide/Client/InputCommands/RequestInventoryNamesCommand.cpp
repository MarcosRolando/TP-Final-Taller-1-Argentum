//
// Created by ivan on 13/7/20.
//

#include "RequestInventoryNamesCommand.h"

MSGPACK_ADD_ENUM(GameType::PlayerEvent)

void RequestInventoryNamesCommand::operator()(std::stringstream &msgBuffer) {
    msgpack::type::tuple<GameType::PlayerEvent> event(GameType::PLAYER_REQUEST_INVENTORY_NAMES);
    msgpack::pack(msgBuffer, event);
}
