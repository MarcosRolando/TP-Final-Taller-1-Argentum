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

    //Intenta agregar el entity a la tile, destruyendo la entity almacenada
    //previamente
    bool addEntity(Entity *received_entity);

    //Intenta agregar el item al tile, destruyendo el item almacenado
    //previamente
    bool addItem(Item *received_item);
};


#endif //ARGENTUM_TILE_H
