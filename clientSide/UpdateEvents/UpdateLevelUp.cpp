//
// Created by marcos on 20/7/20.
//

#include "UpdateLevelUp.h"
#include "../Client/GameGUI.h"

void UpdateLevelUp::operator()(GameGUI &game) {
    game.getMap().updatePlayerLevel(playerNickname, level);
}
