//
// Created by agustin on 9/6/20.
//

#include "Chest.h"

GameType::EquipmentPlace Chest::use(Player &player) {
    return GameType::EQUIPMENT_PLACE_CHEST;
}

bool Chest::isDefault() const {
    return (id == GameType::COMMON_CLOTHING);
}
