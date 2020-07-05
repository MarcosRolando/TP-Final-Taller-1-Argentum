//
// Created by agustin on 23/6/20.
//

#include "Drop.h"
#include "../../Entities/Player.h"


Drop::Drop(Player &_player, unsigned int _position) {
    player = &_player;
    position = _position;
}

Drop::Drop(std::list<std::shared_ptr<Item>>&& _items, unsigned int _position) {
    player = nullptr;
    position = _position;
    items = std::move(_items);
}

void Drop::operator()(ServerProtocol& protocol) {
    if (player) {
        player->dropItem(position);
    } else {

    }
}
