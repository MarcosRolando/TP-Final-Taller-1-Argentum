//
// Created by marcos on 7/9/20.
//

#include "UpdateTeleportEntity.h"
#include "../Client/GameGUI.h"

void UpdateTeleportEntity::operator()(GameGUI &game) {
    bool isMyPlayer = (game.getPlayerInfo().getNickname() == nickname);
    game.getMap().teleportEntity(nickname, newPosition, isMyPlayer);
}
