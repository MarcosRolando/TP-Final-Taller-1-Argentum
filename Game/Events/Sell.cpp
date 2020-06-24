//
// Created by agustin on 23/6/20.
//

#include "Sell.h"
#include "../../Entities/Player.h"

Sell::Sell(Player &player, std::string& _itemName, Coordinate _position):
           player(player), itemName(_itemName) {
    position = _position;
}

void Sell::operator()() {
    player.sellTo(itemName, position);
}
