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

bool Tile::addEntity(Entity *received_entity) {
    if (isOccupable) {
        this->entity.reset(received_entity);
        isOccupable = false;
        return true;
    }
    return false;
}

void Tile::removeEntity() {
    entity.reset(nullptr);
    isOccupable = true;
}

bool Tile::addItem(Item *received_item) {
    if (!item) {
        return false;
    }
    item.reset(received_item);
    return true;
}

void Tile::removeItem() {
    item.reset(nullptr);
}

