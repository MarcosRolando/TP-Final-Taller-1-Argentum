//
// Created by agustin on 9/6/20.
//

#include "Head.h"

Head::Head(unsigned int minDefense, unsigned int maxDefense): Clothing(minDefense, maxDefense){

}

EquipmentPlace Head::use(Player &player) {
    return EQUIPMENT_PLACE_HEAD;
}
