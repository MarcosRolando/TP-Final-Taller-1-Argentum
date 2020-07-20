//
// Created by marcos on 7/2/20.
//

#include "UpdateGUI.h"
#include "../Client/GameGUI.h"

void UpdateGUI::operator()(GameGUI &game) {
    for (const auto & item : data.equippedItems) {
        game.getPlayerInventory().addEquipableItem(std::get<0>(item),
                                                   std::get<1>(item));
    }
    for (const auto & item : data.inventoryItems) {
        game.getPlayerInventory().addInventoryItem(std::get<0>(item),
                                                   std::get<1>(item));
    }
    game.getPlayerInfo().update(data.generalInfo);
    game.getMinichat().receiveText(data.minichatText);
}
