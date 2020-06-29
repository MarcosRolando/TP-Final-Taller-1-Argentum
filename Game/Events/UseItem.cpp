//
// Created by agustin on 23/6/20.
//

#include "UseItem.h"
#include "../../Entities/Player.h"

UseItem::UseItem(Player &player, int _position): player(player) {
    position = _position;
}

void UseItem::operator()(ServerProtocol& protocol) {
    player.useItem(position);
}
