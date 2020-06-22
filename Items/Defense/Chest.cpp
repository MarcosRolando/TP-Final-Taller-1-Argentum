//
// Created by agustin on 9/6/20.
//

#include "Chest.h"

Chest::Chest(GameType::Clothing clothing) : Clothing(clothing) {

}

EquipmentPlace Chest::use(Player &player) {
    return EQUIPMENT_PLACE_CHEST;
}
