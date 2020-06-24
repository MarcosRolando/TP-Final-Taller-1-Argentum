//
// Created by agustin on 23/6/20.
//

#include "Deposit.h"
#include "../../Entities/Player.h"

Deposit::Deposit(Player &_player, std::string &_itemName, Coordinate _npcPosition) : player(_player) {
    itemName = _itemName;
    npcPosition = _npcPosition;
}

//todo implementar metodo deposit en player
void Deposit::operator()() {
    player.deposit(itemName, npcPosition);
}