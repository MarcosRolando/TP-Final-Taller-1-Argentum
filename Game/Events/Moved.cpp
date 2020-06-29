//
// Created by agustin on 29/6/20.
//

#include <sstream>
#include "Moved.h"

#include "../../Entities/Entity.h"
#include "../../Server/ServerProtocol.h"
#include <msgpack.hpp>

MSGPACK_ADD_ENUM(GameType::Direction)
MSGPACK_ADD_ENUM(GameType::EventID)

Moved::Moved(Entity &entity, GameType::Direction _direction, int32_t _displacement):
             entity(entity) {
    direction = _direction;
    displacement = _displacement;
}

void Moved::operator()(ServerProtocol &protocol) {
    std::stringstream data;
    msgpack::type::tuple<GameType::EventID, GameType::Direction, int32_t, std::string>
                        messageTypeData(GameType::MOVED, direction,
                                 entity.executeDisplacement(displacement), entity.getNickname());
    msgpack::pack(data, messageTypeData);
    protocol.addToGeneralData(data);
}
