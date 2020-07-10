//
// Created by ivan on 9/7/20.
//

#include "UpdatePlayerResurrect.h"
#include "../Client/GameGUI.h"

void UpdatePlayerResurrect::operator()(GameGUI &game) {
    game.getMap().revivePlayer(nickname);
}
