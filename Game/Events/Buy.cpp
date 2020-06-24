//
// Created by agustin on 23/6/20.
//

#include "Buy.h"
#include "../../Entities/Player.h"

Buy::Buy(Player &_player, std::string &_itemName, Coordinate _npcPosition) : player(_player) {
    itemName = _itemName;
    npcPosition = _npcPosition;
}

void Buy::operator()() {
    player.buyFrom(itemName, npcPosition);
}
