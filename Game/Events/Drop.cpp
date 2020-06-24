//
// Created by agustin on 23/6/20.
//

#include "Drop.h"
#include "../../Entities/Player.h"


Drop::Drop(Player &player, unsigned int _position): player(player) {
    position = _position;
}

void Drop::operator()() {
    player.dropItem(position);
}
