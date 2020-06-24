//
// Created by agustin on 23/6/20.
//

#include "Move.h"
#include "../../Entities/Player.h"
#include "../../Game/Game.h"

Move::Move(Game &_game, Player &_player, Coordinate _destination) :
                                                game(_game), player(_player) {
    destination = _destination;
}

void Move::operator()() {
    game.moveEntity(player.getPosition(), destination);
}
