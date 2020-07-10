//
// Created by ivan on 10/7/20.
//

#include "WithdrawCommand.h"

MSGPACK_ADD_ENUM(GameType::PlayerEvent)


void WithdrawCommand::operator()(std::stringstream &msgBuffer) {
    msgpack::type::tuple<GameType::PlayerEvent> event(GameType::PLAYER_WITHDRAW);
    msgpack::type::tuple<std::string, int32_t, int32_t> depositInfo;
    depositInfo = {item, tile.i, tile.j};
    msgpack::pack(msgBuffer, event);
    msgpack::pack(msgBuffer, depositInfo);
}
