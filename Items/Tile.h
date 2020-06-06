//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_TILE_H
#define ARGENTUM_TILE_H


#include "Item.h"
#include <memory>

class Tile {
private:
    std::unique_ptr<Item> item;
    std::unique_ptr<Entity> entity;
    bool isOccupable;
public:

};


#endif //ARGENTUM_TILE_H
