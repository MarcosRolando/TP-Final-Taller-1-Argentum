//
// Created by ivan on 10/7/20.
//

#include "HealCommand.h"

MSGPACK_ADD_ENUM(GameType::PlayerEvent)


void HealCommand::operator()(std::stringstream &msgBuffer) {
    msgpack::type::tuple<GameType::PlayerEvent> event(GameType::PLAYER_HEAL);
    msgpack::type::tuple<int32_t, int32_t> selectedTile;
    selectedTile = {tile.i, tile.j};
    msgpack::pack(msgBuffer, event);
    msgpack::pack(msgBuffer, selectedTile);
}
