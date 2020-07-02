//
// Created by marcos on 7/2/20.
//

#include "UpdateCreateNPC.h"
#include "../Client/GameGUI.h"

void UpdateCreateNPC::operator()(GameGUI& game) {
    game.addNPC(data.texture, std::move(data.nickname), data.pos);
}