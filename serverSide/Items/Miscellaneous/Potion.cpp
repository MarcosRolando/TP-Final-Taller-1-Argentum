//
// Created by agustin on 19/6/20.
//

#include "Potion.h"


GameType::EquipmentPlace Potion::use(Player &player) {
    restoreStat(player);
    return GameType::EQUIPMENT_PLACE_NONE;
}

Potion::Potion(GameType::Potion potion):
                Item(GameType::ITEM_TYPE_POTION, Configuration::getInstance().configPotionData(potion).name) {
    recoveryValue = Configuration::getInstance().configPotionData(potion).recoveryValue;
    id = potion;
}