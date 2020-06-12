//
// Created by agustin on 9/6/20.
//

#include "Shield.h"

Shield::Shield(unsigned int minDefense, unsigned int maxDefense) :
               Clothing(minDefense, maxDefense, "SinEscudo") {

}

EquipmentPlace Shield::use(Player &player) {
    return EQUIPMENT_PLACE_SHIELD;
}
