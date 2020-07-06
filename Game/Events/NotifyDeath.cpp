//
// Created by agustin on 5/7/20.
//

#include "NotifyDeath.h"

#include "../../Entities/Player.h"
#include <msgpack.hpp>

MSGPACK_ADD_ENUM(GameType::EventID)

NotifyDeath::NotifyDeath(const Player &player): player(player) {

}

void NotifyDeath::operator()(ServerProtocol &protocol) {
    std::stringstream data;
    msgpack::type::tuple<GameType::EventID> messageTypeData(GameType::PLAYER_DEATH);
    msgpack::pack(data, messageTypeData);
    msgpack::type::tuple<std::string> nicknameData(player.getNickname());
    msgpack::pack(data, nicknameData);
}
