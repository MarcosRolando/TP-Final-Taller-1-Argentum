//
// Created by agustin on 23/6/20.
//

#include "Move.h"
#include "../../Entities/Entity.h"
#include "../../Game/Game.h"

Move::Move(Game &_game, Entity &_entity, GameType::Direction _moveDirection) :
                                                  game(_game), entity(_entity) {
    moveDirection = _moveDirection;
}

void Move::operator()(ServerProtocol& protocol) {
    game.moveEntity(entity.getPosition(), entity.getFinalCoordinate(moveDirection));
}
