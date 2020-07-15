//
// Created by agustin on 14/7/20.
//

#include "ModifyPlayerMovement.h"

#include "../../Entities/Player.h"

ModifyPlayerMovement::ModifyPlayerMovement(Player& player, GameType::Direction _direction): player(player) {
    direction = _direction;
    continuesMovement = true;
}

ModifyPlayerMovement::ModifyPlayerMovement(Player& player): player(player) {
    continuesMovement = false;
}

void ModifyPlayerMovement::operator()(ServerProtocol& protocol) {
    if (continuesMovement) {
        player.startMovement(direction);
    } else {
        player.stopMovement();
    }
}
