//
// Created by agustin on 9/6/20.
//

#include "Chest.h"

Chest::Chest(unsigned int minDefense, unsigned int maxDefense) : Clothing(
             minDefense, maxDefense, "Remera") {

}

EquipmentPlace Chest::use(Player &player) {
    return EQUIPMENT_PLACE_CHEST;
}
