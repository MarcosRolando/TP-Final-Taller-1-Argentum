//
// Created by agustin on 23/6/20.
//

#include "Move.h"
#include "../../Entities/Entity.h"
#include "../../Game/Game.h"

Move::Move(Game &_game, Entity &_entity, Coordinate _destination) :
                                                game(_game), entity(_entity) {
    destination = _destination;
}

void Move::operator()() {
    game.moveEntity(entity.getPosition(), destination);
}
