//
// Created by agustin on 23/6/20.
//

#include "Buy.h"
#include "../../Entities/Player.h"

Buy::Buy(Player &_player, std::string &_itemName) : player(_player) {
    itemName = _itemName;
}


void Buy::operator()() {
    player.buy(player, itemName);
}
