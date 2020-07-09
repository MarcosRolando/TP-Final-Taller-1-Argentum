//
// Created by ivan on 9/7/20.
//

#include "PickUpCommand.h"

MSGPACK_ADD_ENUM(GameType::PlayerEvent)

void PickUpCommand::operator()(std::stringstream &msgBuffer) {
    msgpack::type::tuple<GameType::PlayerEvent> event(GameType::PLAYER_PICK_UP);
    msgpack::pack(msgBuffer, event);
}
