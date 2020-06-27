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

void Item::loadDropItemData(std::stringstream &buffer, uint32_t i, uint32_t j) const {
    msgpack::type::tuple<GameType::ID> idType(GameType::ITEM);
    msgpack::type::tuple<GameType::ItemType, int32_t, uint32_t, uint32_t>
                                        data(type, id, i, j);
    msgpack::pack(buffer, idType);
    msgpack::pack(buffer, data);
}

void Item::loadEquippedData(std::stringstream &buffer) {
    msgpack::type::tuple<GameType::ItemType, int32_t> data(type, id);
    msgpack::pack(buffer, data);
}
