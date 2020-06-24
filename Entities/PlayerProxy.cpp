//
// Created by marcos on 23/6/20.
//

#include "PlayerProxy.h"
#include "../Map/Coordinate.h"
#include "../Game/Game.h"
#include "../Game/Events/Attack.h"
#include "../Entities/Player.h"

void PlayerProxy::attack(Coordinate target) {
    std::unique_ptr<Attack> event(new Attack(player, target));
    game.pushEvent(std::move(event));
}

void PlayerProxy::useItem(int itemPosition) {

}

void PlayerProxy::meditate() {
    player.meditate();
}

void PlayerProxy::move(Direction direction) {
    player.requestMove(direction);
}
