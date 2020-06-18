//
// Created by agustin on 6/6/20.
//

#include "Gold.h"


Gold::Gold(unsigned int amount/* = 0*/): Item("Oro"){
    this->amount = amount;
}

EquipmentPlace Gold::use(Player &player) {
    return EQUIPMENT_PLACE_NONE;
}

unsigned int Gold::getamount() {
    return amount;
}
