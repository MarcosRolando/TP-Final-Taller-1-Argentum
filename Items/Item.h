//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_ITEM_H
#define ARGENTUM_ITEM_H

#include "../Entities/Player.h"

enum EquipmentPlace{
    EQUIPMENT_PLACE_NONE, EQUIPMENT_PLACE_HEAD, EQUIPMENT_PLACE_CHEST, EQUIPMENT_PLACE_WEAPON,
    EQUIPMENT_PLACE_SHIELD
};


//Clase interfaz de la que heredan todos los items
//Los items solo tienen sentido en un inventario de un jugador
class Item {
public:
    //use debe retornar el lugar en el que debera equiparse el item una vez usado desde
    //un inventario, si debe ser descartado entonces se tiene que retornar INVENTORY_PLACE_NONE
    //Esta funcion retorna en cierta forma el tipo de item que es
    virtual EquipmentPlace use(Player& player);
};


#endif //ARGENTUM_ITEM_H