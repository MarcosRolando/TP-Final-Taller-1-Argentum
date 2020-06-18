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
