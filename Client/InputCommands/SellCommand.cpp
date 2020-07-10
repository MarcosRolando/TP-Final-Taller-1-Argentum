//
// Created by ivan on 9/7/20.
//

#include "SellCommand.h"

MSGPACK_ADD_ENUM(GameType::PlayerEvent)


void SellCommand::operator()(std::stringstream &msgBuffer) {
    msgpack::type::tuple<GameType::PlayerEvent> event(GameType::PLAYER_SELL);
    msgpack::type::tuple<std::string, int32_t, int32_t> saleInfo;
    saleInfo = {item, tile.i, tile.j};
    msgpack::pack(msgBuffer, event);
    msgpack::pack(msgBuffer, saleInfo);
}
