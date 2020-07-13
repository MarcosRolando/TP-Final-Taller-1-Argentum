//
// Created by ivan on 1/7/20.
//

#include "UpdateCreatePlayer.h"
#include "../Client/GameGUI.h"

void UpdateCreatePlayer::operator()(GameGUI& game) {
    game.addPlayer(data);
}
