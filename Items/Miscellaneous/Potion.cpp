//
// Created by agustin on 19/6/20.
//

#include "Potion.h"


GameType::EquipmentPlace Potion::use(Player &player) {
    restoreStat(player);
    return GameType::EQUIPMENT_PLACE_NONE;
}

Potion::Potion(const Config::PotionData& data): Item(GameType::ITEM_TYPE_POTION, data.name) {
    recoveryValue = data.recoveryValue;
}

Potion::~Potion() = default;