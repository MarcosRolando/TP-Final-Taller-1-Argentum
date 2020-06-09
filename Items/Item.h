//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_ITEM_H
#define ARGENTUM_ITEM_H

#include "../Entities/Player.h"

enum InventoryPLace{
    INVENTORY_PLACE_NONE, INVENTORY_PLACE_HEAD, INVENTORY_PLACE_CHEST, INVENTORY_PLACE_WEAPON,
    INVENTORY_PLACE_SHIELD
};


//Clase interfaz de la que heredan todos los items
//Los items solo tienen sentido en un inventario de un jugador
class Item {
public:
    //use debe retornar el lugar en el que debera equiparse el item una vez usado desde
    //un inventario, si debe ser descartado entonces se tiene que retornar INVENTORY_PLACE_NONE
    virtual InventoryPlace use(Player& player) = 0;
};


#endif //ARGENTUM_ITEM_H
