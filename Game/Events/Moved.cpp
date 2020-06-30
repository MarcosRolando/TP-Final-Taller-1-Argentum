//
// Created by agustin on 29/6/20.
//

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
    msgpack::type::tuple<GameType::EventID> messageTypeData(GameType::MOVED);
    msgpack::pack(data, messageTypeData);
    bool hasFinishedMoving;
    int32_t realDisplacement = entity.executeDisplacement(displacement, hasFinishedMoving);
    msgpack::type::tuple<GameType::Direction, int32_t, std::string, bool>
                        eventData(direction, realDisplacement, entity.getNickname(), hasFinishedMoving);
    msgpack::pack(data, eventData);
    protocol.addToGeneralData(data);
}
