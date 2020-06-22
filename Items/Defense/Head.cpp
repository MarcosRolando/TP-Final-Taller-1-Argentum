//
// Created by agustin on 9/6/20.
//

#include "Head.h"

Head::Head(GameType::Clothing clothing) : Clothing(clothing) {

}

EquipmentPlace Head::use(Player &player) {
    return EQUIPMENT_PLACE_HEAD;
}

bool Head::isDefault() const {
    return (id == GameType::NO_HELMET);
}
