//
// Created by agustin on 23/6/20.
//

#include "Drop.h"
#include "../../Entities/Player.h"


Drop::Drop(Player &player, unsigned int _position): player(&player) {
    position = _position;
}

Drop::Drop(std::list<std::shared_ptr<Item>>&& items, unsigned int position) {

}

void Drop::operator()(ServerProtocol& protocol) {
    if (player) {
        player->dropItem(position);
    }
}
