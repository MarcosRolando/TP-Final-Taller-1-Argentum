//
// Created by agustin on 6/6/20.
//

#include "Tile.h"

bool Tile::addEntity(Item *item) {
    if (isOccupable) {
        this->item = item;
        return true;
    }
    return false;
}
