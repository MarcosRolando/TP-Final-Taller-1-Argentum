//
// Created by agustin on 9/6/20.
//

#include "Chest.h"

using namespace Config;

/*
Chest::Chest(unsigned int minDefense, unsigned int maxDefense) : Clothing(
             minDefense, maxDefense, "Remera") {

}
*/

Chest::Chest(Config::ClothingStats stats, const std::string &name) : Clothing(stats, name) {

}

EquipmentPlace Chest::use(Player &player) {
    return EQUIPMENT_PLACE_CHEST;
}
