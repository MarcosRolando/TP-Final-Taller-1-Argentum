//
// Created by agustin on 6/6/20.
//

#include "Gold.h"
#include "../../Config/Configuration.h"

Gold::Gold(unsigned int amount): Item(GameType::ITEM_TYPE_GOLD,
                    Configuration::getInstance().configGetGoldName()/*, 0*/){
    this->amount = amount;
}

GameType::EquipmentPlace Gold::use(Player &player) {
    return GameType::EQUIPMENT_PLACE_NONE;
}

unsigned int Gold::getAmmount() const {
    return amount;
}

bool Gold::isGold() const {
    return true;
}
