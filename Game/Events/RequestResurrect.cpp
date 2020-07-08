//
// Created by agustin on 8/7/20.
//

#include "RequestResurrect.h"

#include "../../Entities/Player.h"
#include "../Game.h"
#include <msgpack.hpp>
#include "../../Server/ServerProtocol.h"

MSGPACK_ADD_ENUM(GameType::EventID)

RequestResurrect::RequestResurrect(Game& game, Player& player, Coordinate _selectedPosition)
                                        : player(player), game(game) {
    selectedPosition = _selectedPosition;
}

void RequestResurrect::operator()(ServerProtocol &protocol) {
    if (game.requestResurrect(player, selectedPosition)) {
        std::stringstream data;
        msgpack::type::tuple<GameType::EventID> messageTypeData(GameType::RESURRECTED);
        msgpack::pack(data, messageTypeData);
        msgpack::type::tuple<std::string> playerData(player.getNickname());
        msgpack::pack(data, playerData);
        protocol.addToGeneralData(data);
    }
}
