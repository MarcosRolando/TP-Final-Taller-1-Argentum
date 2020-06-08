//
// Created by agustin on 7/6/20.
//

#include "Map.h"

unsigned int Map::attackTile(unsigned int damage, unsigned int level,
                             Coordinate coordinate) {
    return tiles[coordinate.position_i][coordinate.position_j].attacked(damage, level);
}
