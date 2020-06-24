//
// Created by agustin on 23/6/20.
//

#include "Buy.h"
#include "../../Entities/Player.h"

Buy::Buy(Player &_player, std::string &_itemName, Coordinate _npcPosition) : player(_player) {
    itemName = _itemName;
    npcPosition = _npcPosition;
}

//todo implementar metodo buy en player
void Buy::operator()() {
    player.buy(player, itemName, npcPosition);
}
