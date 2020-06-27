//
// Created by agustin on 9/6/20.
//

#include "Item.h"
#include <msgpack.hpp>

MSGPACK_ADD_ENUM(GameType::ID)
MSGPACK_ADD_ENUM(GameType::ItemType)

Item::Item(GameType::ItemType _type, const std::string &_name): name(_name) {
    type = _type;
}

EquipmentPlace Item::use(Player &player) {
    return EQUIPMENT_PLACE_NONE;
}

const std::string &Item::getName() const {
    return name;
}

bool Item::isGold() const {
    return false;
}

void Item::operator>>(std::stringstream &buffer) const {
    msgpack::type::tuple<GameType::ID, GameType::ItemType, unsigned int> /*El cliente tendra que chequear el ItemType e interpretar el id con el enum que corresponda*/
            data(GameType::ITEM, type, id);
    msgpack::pack(buffer, data);
}
