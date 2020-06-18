//
// Created by agustin on 7/6/20.
//

#include "Game.h"

unsigned int Game::attackPosition(int damage, unsigned int level,
                              Coordinate coordinate) {
    return map.attackTile(damage, level, coordinate);
}
