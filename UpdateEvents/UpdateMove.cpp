//
// Created by marcos on 6/29/20.
//

#include "UpdateMove.h"
#include "../Map/Map.h"

#include "../Client/GameGUI.h"

void UpdateMove::operator()(GameGUI& game) {
    game.getMap().moveEntity(nickname, direction, distanceTravelled,
                                                            reachedDestination);
}
