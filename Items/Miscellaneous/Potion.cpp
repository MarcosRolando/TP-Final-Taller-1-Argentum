//
// Created by agustin on 19/6/20.
//

#include "Potion.h"


EquipmentPlace Potion::use(Player &player) {
    restoreStat(player);
    return EQUIPMENT_PLACE_NONE;
}

Potion::Potion(const Config::PotionData& data): Item(ITEM_TYPE_POTION, data.name, data.price) {
    recoveryValue = data.recoveryValue;
}
