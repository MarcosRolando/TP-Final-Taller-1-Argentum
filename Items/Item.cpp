//
// Created by agustin on 9/6/20.
//

#include "Item.h"
#include <utility>

Item::Item(const std::string &_name) {
    name = _name;
}

Item::Item(std::string &&_name) {
    name = std::move(_name);
}

EquipmentPlace Item::use(Player &player) {
    return EQUIPMENT_PLACE_NONE;
}

const std::string &Item::getName() {
    return name;
}


