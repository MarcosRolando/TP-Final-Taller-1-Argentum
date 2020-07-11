//
// Created by agustin on 23/6/20.
//

#include "Deposit.h"
#include "../../Entities/Player.h"

Deposit::Deposit(Player &_player, std::string&& _itemName, Coordinate _npcPosition) : player(_player) {
    itemName = std::move(_itemName);
    npcPosition = _npcPosition;
}

void Deposit::operator()(ServerProtocol& protocol) {
    player.depositTo(itemName, npcPosition);
}
