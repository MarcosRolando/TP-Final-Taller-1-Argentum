//
// Created by marcos on 7/3/20.
//

#include "UpdateRemoveEntity.h"
#include "../Client/GameGUI.h"

void UpdateRemoveEntity::operator()(GameGUI &game) {
    game.getMap().removeEntity(nickname);
}
