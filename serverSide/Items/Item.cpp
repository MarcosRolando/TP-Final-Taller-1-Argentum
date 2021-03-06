//
// Created by agustin on 9/6/20.
//

#include "Item.h"
#include <msgpack.hpp>

MSGPACK_ADD_ENUM(GameType::EventID)
MSGPACK_ADD_ENUM(GameType::ItemType)

Item::Item(GameType::ItemType _type, const std::string &_name): name(_name) {
    type = _type;
}

GameType::EquipmentPlace Item::use(Player &player) {
    return GameType::EQUIPMENT_PLACE_NONE;
}

const std::string &Item::getName() const {
    return name;
}

bool Item::isGold() const {
    return false;
}

void Item::loadDropItemData(std::stringstream &buffer, int32_t i, int32_t j) const {
    msgpack::type::tuple<GameType::EventID> idType(GameType::CREATE_ITEM);
    msgpack::type::tuple<GameType::ItemType, int32_t, int32_t, int32_t>
                                        data(type, id, i, j);
    msgpack::pack(buffer, idType);
    msgpack::pack(buffer, data);
}

void Item::loadEquippedItemData(std::stringstream &buffer) {
    msgpack::type::tuple<int32_t> data(id);
    msgpack::pack(buffer, data);
}

void Item::loadTypeAndId(std::stringstream &buffer) {
    msgpack::type::tuple<GameType::ItemType, int32_t> data(type, id);
    msgpack::pack(buffer, data);
}

int32_t Item::getId() {
    return id;
}

GameType::ItemType Item::getType() {
    return type;
}
