//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_TILE_H
#define ARGENTUM_TILE_H

#include <memory>
#include "../Items/Item.h"
#include "FloorType.h"
#include "../Entities/Entity.h"

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

    //Elimina la entity guardada, habilita la ocupacion del tile por otra
    //entity
    //La funcion no chequea si el tile es ocupable o no debido a FloorType,
    //una llamada a esa funcion en un tile no ocupable lo hara ocupable
    //independientemente del tile
    void removeEntity();

    //Intenta agregar el item al tile, destruyendo el item almacenado
    //previamente
    bool addItem(Item *received_item);

    //Elimina el item guardado, habilita la ocupacion del tile por otro
    //item
    void removeItem();
};


#endif //ARGENTUM_TILE_H
