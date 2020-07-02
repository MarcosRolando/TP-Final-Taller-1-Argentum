//
// Created by agustin on 23/6/20.
//

#include "Attack.h"
#include "../../Entities/Entity.h"
#include "../../Server/ServerProtocol.h"
#include "msgpack.hpp"

MSGPACK_ADD_ENUM(GameType::EventID)

Attack::Attack(Entity& _entity, Coordinate _target) : entity(_entity) {
    target = _target;
}

void Attack::operator()(ServerProtocol& protocol) {
    entity.attack(target);
    std::stringstream data;
    msgpack::type::tuple<GameType::EventID> messageTypeData(GameType::ATTACK);
    msgpack::pack(data, messageTypeData);
    msgpack::type::tuple<int32_t, int32_t> attackCoordinateData(target.iPosition, target.jPosition);
    msgpack::pack(data, attackCoordinateData);
    protocol.addToGeneralData(data);
}