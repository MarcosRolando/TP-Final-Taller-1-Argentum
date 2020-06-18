//
// Created by agustin on 9/6/20.
//

#include "Head.h"

using namespace Config;

/*
//VER SI SACO EL STRING LITERAL DE ACA
Head::Head(unsigned int minDefense, unsigned int maxDefense): Clothing(minDefense, maxDefense, "Cabeza"){

}
*/

Head::Head(ClothingStats stats, const std::string& name): Clothing(stats, name) {

}

EquipmentPlace Head::use(Player &player) {
    return EQUIPMENT_PLACE_HEAD;
}
