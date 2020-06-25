//
// Created by agustin on 9/6/20.
//

#include "Shield.h"

Shield::Shield(GameType::Clothing clothing): Clothing(clothing) {

}

EquipmentPlace Shield::use(Player &player) {
    return EQUIPMENT_PLACE_SHIELD;
}

bool Shield::isDefault() const {
    return (static_cast<GameType::Clothing>(id) == GameType::Clothing::NO_SHIELD);
}
