//
// Created by ivan on 9/7/20.
//

#include "BuyCommand.h"

MSGPACK_ADD_ENUM(GameType::PlayerEvent)

void BuyCommand::operator()(std::stringstream &msgBuffer) {
    msgpack::type::tuple<GameType::PlayerEvent> event(GameType::PLAYER_BUY);
    msgpack::type::tuple<std::string, int32_t, int32_t> buyInfo;
    buyInfo = {item, tile.i, tile.j};
    msgpack::pack(msgBuffer, event);
    msgpack::pack(msgBuffer, buyInfo);
}
