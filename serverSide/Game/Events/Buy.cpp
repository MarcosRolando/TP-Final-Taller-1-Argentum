//
// Created by agustin on 23/6/20.
//

#include "Buy.h"
#include "../../Entities/Player.h"

Buy::Buy(Player &_player, std::string&& _itemName, Coordinate _npcPosition) : player(_player) {
    itemName = std::move(_itemName);
    npcPosition = _npcPosition;
}

void Buy::operator()(ServerProtocol& protocol) {
    player.buyFrom(itemName, npcPosition);
}
