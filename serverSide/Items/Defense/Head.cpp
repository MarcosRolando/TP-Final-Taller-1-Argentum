//
// Created by agustin on 9/6/20.
//

#include "Head.h"

Head::Head(GameType::Clothing clothing) : Clothing(clothing) {

}

GameType::EquipmentPlace Head::use(Player &player) {
    return GameType::EQUIPMENT_PLACE_HEAD;
}

bool Head::isDefault() const {
    return (static_cast<GameType::Clothing>(id) == GameType::Clothing::NO_HELMET);
}
