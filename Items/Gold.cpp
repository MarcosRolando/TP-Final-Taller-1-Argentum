//
// Created by agustin on 6/6/20.
//

#include "Gold.h"


Gold::Gold(unsigned int ammount/* = 0*/): Item("Oro"){
    this->ammount = ammount;
}

EquipmentPlace Gold::use(Player &player) {
    return EQUIPMENT_PLACE_NONE;
}

unsigned int Gold::getAmmount() {
    return ammount;
}

std::shared_ptr<Item> Gold::getInstance() {
    std::shared_ptr<Item> gold(new Gold(0));
    return gold;
}

std::shared_ptr<Item> Gold::getInstance(unsigned int storedGold) {
    std::shared_ptr<Item> gold(new Gold(storedGold));
    return gold;
}
