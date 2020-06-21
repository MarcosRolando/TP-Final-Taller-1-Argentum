//
// Created by agustin on 19/6/20.
//

#include "Potion.h"


EquipmentPlace Potion::use(Player &player) {
    restoreStat(player);
    return EQUIPMENT_PLACE_NONE;
}

/*
Potion::Potion(GameType::Potion potion): Item(Configuration::getInstance().configPotionData(potion).name,
                                              Configuration::getInstance().configPotionData(potion).price) {

    recoveryValue = Configuration::getInstance().configPotionData(potion).recoveryValue;
}
*/

Potion::Potion(const Config::PotionData& data): Item(data.name, data.price) {
    recoveryValue = data.recoveryValue;
}
