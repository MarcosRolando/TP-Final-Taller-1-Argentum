//
// Created by agustin on 20/7/20.
//

#include "PlayerLeveledUp.h"

#include "../../../libs/GameEnums.h"
#include "../../Server/ServerProtocol.h"
#include <msgpack.hpp>

MSGPACK_ADD_ENUM(GameType::EventID)

PlayerLeveledUp::PlayerLeveledUp(const std::string &playerNickname, int32_t _level):
                                 playerNickname(playerNickname) {
    level = _level;
}

void PlayerLeveledUp::operator()(ServerProtocol &protocol) {
    std::stringstream data;
    msgpack::type::tuple<GameType::EventID> messageTypeData(GameType::PLAYER_LEVEL_UP);
    msgpack::pack(data, messageTypeData);
    msgpack::type::tuple<std::string, int32_t> nicknameData(playerNickname, level);
    msgpack::pack(data, nicknameData);
    protocol.addToGeneralData(data);
}
