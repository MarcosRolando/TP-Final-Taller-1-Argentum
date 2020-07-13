//
// Created by marcos on 9/7/20.
//

#include "UpdateDestroyItem.h"
#include "../Client/GameGUI.h"

void UpdateDestroyItem::operator()(GameGUI &game) {
    game.getMap().destroyItem(position);
}
