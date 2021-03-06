//
// Created by agustin on 23/6/20.
//

#include "List.h"
#include "../../Entities/Player.h"

List::List(Player &_player, Coordinate _npcPosition) : player(_player) {
    npcPosition = _npcPosition;
}

void List::operator()(ServerProtocol& protocol) {
    player.listFrom(npcPosition);
}