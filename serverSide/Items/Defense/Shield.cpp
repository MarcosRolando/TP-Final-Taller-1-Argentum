//
// Created by agustin on 9/6/20.
//

#include "Shield.h"

Shield::Shield(GameType::Clothing clothing): Clothing(clothing) {

}

GameType::EquipmentPlace Shield::use(Player &player) {
    return GameType::EQUIPMENT_PLACE_SHIELD;
}

bool Shield::isDefault() const {
    return (static_cast<GameType::Clothing>(id) == GameType::Clothing::NO_SHIELD);
}
