//
// Created by agustin on 23/6/20.
//

#include "Unequip.h"
#include "../../Entities/Player.h"
#include "../../Items/Item.h"
#include "../../Server/ServerProtocol.h"
#include "msgpack.hpp"

MSGPACK_ADD_ENUM(GameType::EventID)
MSGPACK_ADD_ENUM(GameType::EquipmentPlace)

Unequip::Unequip(Player &player, GameType::EquipmentPlace _equipment): player(player) {
    equipment = _equipment;
}

void Unequip::operator()(ServerProtocol& protocol) {
    bool hasAppearanceChanged;
    if (equipment == GameType::EQUIPMENT_PLACE_WEAPON) {
        hasAppearanceChanged = player.unequip();
    } else {
        hasAppearanceChanged = player.unequip(equipment);
    }
    if (hasAppearanceChanged) {
        std::stringstream data;
        msgpack::type::tuple<GameType::EventID> messageTypeData(GameType::UNEQUIP);
        msgpack::pack(data, messageTypeData);
        msgpack::type::tuple<std::string, GameType::EquipmentPlace>
                unequipData(player.getNickname(), equipment);
        msgpack::pack(data, unequipData);
        protocol.addToGeneralData(data);
    }
}