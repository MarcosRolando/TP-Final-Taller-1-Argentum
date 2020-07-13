//
// Created by marcos on 7/5/20.
//

#include "UpdatePlayerDeath.h"
#include "../Client/GameGUI.h"

void UpdatePlayerDeath::operator()(GameGUI &game) {
    game.getMap().killPlayer(nickname);
}
