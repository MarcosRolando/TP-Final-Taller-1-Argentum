//
// Created by agustin on 10/7/20.
//

#include "RestoreStats.h"

#include "../../Entities/Player.h"
#include "../Game.h"

RestoreStats::RestoreStats(Game &game, Player &player, Coordinate _target): game(game), player(player) {
    target = _target;
}

void RestoreStats::operator()(ServerProtocol &serverProtocol) {
    game.requestRestore(player, target);
}
