//
// Created by ivan on 10/7/20.
//

#include "MessageToPlayerCommand.h"

MSGPACK_ADD_ENUM(GameType::PlayerEvent)


void MessageToPlayerCommand::operator()(std::stringstream &msgBuffer) {
    msgpack::type::tuple<GameType::PlayerEvent> event(GameType::PLAYER_SEND_MSG);
    msgpack::type::tuple<std::string, std::string> msgInfo;
    msgInfo = {nickname, msg};
    msgpack::pack(msgBuffer, event);
    msgpack::pack(msgBuffer, msgInfo);
}
