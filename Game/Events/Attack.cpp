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
    int32_t usedWeapon = entity.attack(target);
    if (usedWeapon != -1) {
        std::stringstream data;
        msgpack::type::tuple<GameType::EventID> messageTypeData(GameType::ATTACK);
        msgpack::pack(data, messageTypeData);
        msgpack::type::tuple<int32_t, int32_t, int32_t> attackCoordinateData
                                (target.iPosition, target.jPosition, usedWeapon);
        msgpack::pack(data, attackCoordinateData);
        protocol.addToGeneralData(data);
    }
}