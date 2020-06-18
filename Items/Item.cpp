//
// Created by agustin on 9/6/20.
//

#include "Item.h"
#include <utility>

Item::Item(const std::string &_name, unsigned int _price) {
    name = _name;
    price = _price;
}

Item::Item(std::string &&_name, unsigned int _price) {
    name = std::move(_name);
    price = _price;
}

EquipmentPlace Item::use(Player &player) {
    return EQUIPMENT_PLACE_NONE;
}

const std::string &Item::getName() const {
    return name;
}

unsigned int Item::getPrice() const {
    return price;
}
