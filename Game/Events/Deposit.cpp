//
// Created by agustin on 23/6/20.
//

#include "Deposit.h"
#include "../../Entities/Player.h"

Deposit::Deposit(Player &_player, const std::string &_itemName, Coordinate _npcPosition) : player(_player) {
    itemName = _itemName;
    npcPosition = _npcPosition;
}

void Deposit::operator()(ServerProtocol& protocol) {
    player.depositTo(itemName, npcPosition);
}
