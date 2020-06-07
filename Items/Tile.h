//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_TILE_H
#define ARGENTUM_TILE_H

#include <memory>
#include "Item.h"
#include "FloorType.h"

class Tile {
private:
    std::unique_ptr<Item> item;
    std::unique_ptr<Entity> entity;
    bool isOccupable;
    FloorType floor;

public:
    //Inicializa el tile, dependiendo tel tipo de piso que reciba seteara el
    //tile como ocupable o no ocupable
    Tile(FloorType floor);
    bool addEntity(Item* item);
};


#endif //ARGENTUM_TILE_H
