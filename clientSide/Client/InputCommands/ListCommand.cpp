//
// Created by ivan on 9/7/20.
//

#include "ListCommand.h"

MSGPACK_ADD_ENUM(GameType::PlayerEvent)

void ListCommand::operator()(std::stringstream &msgBuffer) {
    msgpack::type::tuple<GameType::PlayerEvent> event(GameType::PLAYER_LIST);
    msgpack::type::tuple<int32_t, int32_t> selectedTile;
    selectedTile = {tile.i, tile.j};
    msgpack::pack(msgBuffer, event);
    msgpack::pack(msgBuffer, selectedTile);
}
