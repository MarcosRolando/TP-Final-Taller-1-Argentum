//
// Created by ivan on 10/7/20.
//

#include "DepositCommand.h"

MSGPACK_ADD_ENUM(GameType::PlayerEvent)

void DepositCommand::operator()(std::stringstream &msgBuffer) {
    msgpack::type::tuple<GameType::PlayerEvent> event(GameType::PLAYER_DEPOSIT);
    msgpack::type::tuple<std::string, int32_t, int32_t> depositInfo;
    depositInfo = {item, tile.i, tile.j};
    msgpack::pack(msgBuffer, event);
    msgpack::pack(msgBuffer, depositInfo);
}
