//
// Created by marcos on 23/6/20.
//

#include "PlayerProxy.h"
#include "../Map/Coordinate.h"
#include "../Game/Game.h"
#include "../Game/Events/Attack.h"

void PlayerProxy::attack(Coordinate target) {
    game.pushEvent(std::unique_ptr<Attack>new Attack(player, target));
}
