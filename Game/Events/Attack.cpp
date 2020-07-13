//
// Created by agustin on 23/6/20.
//

#include "Attack.h"
#include "../../Entities/Entity.h"
#include "../../Server/ServerProtocol.h"
#include "msgpack.hpp"

MSGPACK_ADD_ENUM(GameType::Direction)
MSGPACK_ADD_ENUM(GameType::EventID)

Attack::Attack(Entity& _entity, Coordinate _target) : entity(_entity) {
    target = _target;
}

void Attack::operator()(ServerProtocol& protocol) {
    int32_t usedWeapon = entity.attack(target);
    if (usedWeapon != -1) {
        GameType::Direction attackDir = _attackDirection(entity.getPosition());
        std::stringstream data;
        msgpack::type::tuple<GameType::EventID> messageTypeData(GameType::ATTACK);
        msgpack::pack(data, messageTypeData);
        msgpack::type::tuple<std::string, int32_t, int32_t, int32_t,
                                    GameType::Direction> attackCoordinateData
                                (entity.getNickname(), target.iPosition, target.jPosition,
                                        usedWeapon, attackDir);
        msgpack::pack(data, attackCoordinateData);
        protocol.addToGeneralData(data);
    }
}

GameType::Direction Attack::_attackDirection(Coordinate attackerPosition) const {
    if (attackerPosition.iPosition == target.iPosition) {
        if (attackerPosition.jPosition > target.jPosition) {
            return GameType::DIRECTION_LEFT;
        } else {
            return GameType::DIRECTION_RIGHT;
        }
    } else {
        if (attackerPosition.iPosition < target.iPosition) {
            return GameType::DIRECTION_DOWN;
        } else {
            return GameType::DIRECTION_UP;
        }
    }
}
