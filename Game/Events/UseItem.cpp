//
// Created by agustin on 23/6/20.
//

#include "UseItem.h"
#include "../../Entities/Player.h"
#include "../../Config/GameEnums.h"
#include "../../Items/UseReturnData.h"
#include <msgpack.hpp>

MSGPACK_ADD_ENUM(GameType::EventID)
MSGPACK_ADD_ENUM(GameType::EquipmentPlace)

UseItem::UseItem(Player &player, int _position): player(player) {
    position = _position;
}

void UseItem::operator()(ServerProtocol& protocol) {
    UseReturnData useData = player.useItem(position);
    if (useData.equipmentPlace != GameType::EQUIPMENT_PLACE_NONE) {
        std::stringstream data;
        msgpack::type::tuple<GameType::EventID> messageTypeData(GameType::MOVED);
        msgpack::pack(data, messageTypeData);
        msgpack::type::tuple<GameType::EquipmentPlace, int32_t> useDataTuple
                        (useData.equipmentPlace, useData.id);
        msgpack::pack(data, useDataTuple);
    }
}
