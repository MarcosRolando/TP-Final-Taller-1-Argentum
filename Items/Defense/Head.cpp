//
// Created by agustin on 9/6/20.
//

#include "Head.h"

//VER SI SACO EL STRING LITERAL DE ACA
Head::Head(unsigned int minDefense, unsigned int maxDefense): Clothing(minDefense, maxDefense, "Cabeza"){

}

EquipmentPlace Head::use(Player &player) {
    return EQUIPMENT_PLACE_HEAD;
}
