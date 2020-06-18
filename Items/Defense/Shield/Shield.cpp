//
// Created by agustin on 9/6/20.
//

#include "Shield.h"

using namespace Config;

/*
Shield::Shield(unsigned int minDefense, unsigned int maxDefense) :
               Clothing(minDefense, maxDefense, "SinEscudo") {

}
*/

Shield::Shield(ClothingStats stats, const std::string& name): Clothing(stats, name) {

}

EquipmentPlace Shield::use(Player &player) {
    return EQUIPMENT_PLACE_SHIELD;
}
