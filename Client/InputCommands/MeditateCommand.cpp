//
// Created by ivan on 7/7/20.
//

#include "MeditateCommand.h"
#include <msgpack.hpp>
#include "../../Shared/GameEnums.h"
MSGPACK_ADD_ENUM(GameType::PlayerEvent)


void MeditateCommand::operator()(std::stringstream& msgBuffer) {
    msgpack::type::tuple<GameType::PlayerEvent> event(GameType::PLAYER_MEDITATE);
    msgpack::pack(msgBuffer, event);
}
