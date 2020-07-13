//
// Created by ivan on 9/7/20.
//

#include "ResurrectCommand.h"

MSGPACK_ADD_ENUM(GameType::PlayerEvent)


void ResurrectCommand::operator()(std::stringstream &msgBuffer) {
    msgpack::type::tuple<GameType::PlayerEvent> event(GameType::PLAYER_RESURRECT);
    msgpack::type::tuple<int32_t, int32_t> selectedTile;
    selectedTile = {tile.i, tile.j};
    msgpack::pack(msgBuffer, event);
    msgpack::pack(msgBuffer, selectedTile);
}
