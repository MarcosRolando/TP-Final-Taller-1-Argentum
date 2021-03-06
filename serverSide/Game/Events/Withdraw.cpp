//
// Created by agustin on 23/6/20.
//

#include "Withdraw.h"
#include "../../Entities/Player.h"

Withdraw::Withdraw(Player &_player, std::string&& _itemName, Coordinate _npcPosition) : player(_player) {
    itemName = std::move(_itemName);
    npcPosition = _npcPosition;
}

void Withdraw::operator()(ServerProtocol& protocol) {
    player.withdrawFrom(itemName, npcPosition);
}