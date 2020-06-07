//
// Created by agustin on 6/6/20.
//

#include "Tile.h"
#include "FloorType.h"

Tile::Tile(FloorType floor): item(nullptr), entity(nullptr){
    this->floor = floor;
    switch (floor) {
        case FLOOR_TYPE_TREE:
        case FLOOR_TYPE_WALL:
            isOccupable = false;
            break;
        default:
            isOccupable = true;
    }
}

bool Tile::addEntity(Item* received_item) {
    if (isOccupable) {
        //this->item.release();
        this->item.reset(received_item);
        return true;
    }
    return false;
}