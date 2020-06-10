//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_TILE_H
#define ARGENTUM_TILE_H

#include <memory>
#include <list>
#include "../Items/Item.h"
#include "FloorType.h"
#include "../Entities/Entity.h"

class Tile {
private:
    std::unique_ptr<Entity> entity;
    std::list<std::shared_ptr<Item>> items;
    bool isOccupable;
    FloorType floor;

public:
    //Inicializa el tile, dependiendo tel tipo de piso que reciba seteara el
    //tile como ocupable o no ocupable
    explicit Tile(FloorType floor);

    //Constructor por movimiento, intercambia las entities de las tiles
    Tile(Tile&& other) noexcept;

    //Intenta agregar el entity a la tile, destruyendo la entity almacenada
    //previamente
    bool addEntity(Entity *received_entity);

    //Elimina la entity guardada, habilita la ocupacion del tile por otra
    //entity
    //La funcion no chequea si el tile es ocupable o no debido a FloorType,
    //una llamada a esa funcion en un tile no ocupable lo hara ocupable
    //independientemente del tile
    void removeEntity();

    //Intenta agregar el item al tile, sumandolo a los items ya guardados
    void addItem(Item *received_item);

    //Elimina uno de los items que se encuentran en el tile y lo retorna}
    //Si no hay ningun item retorna nullptr
    std::shared_ptr<Item> removeItem();

    //Ataca la entidad que se encuentre guardada en el mapa
    //Retorna la cantidad de daño que recibio la entidad atacada, si no hay
    //una entidad retorna 0
    unsigned int attacked(unsigned int damage, unsigned int level);

    //Retorna true si almacena un entity que es un target de un monster
    bool hasMonsterTarget() const;
};


#endif //ARGENTUM_TILE_H