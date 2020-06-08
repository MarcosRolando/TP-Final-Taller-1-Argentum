//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_ITEM_H
#define ARGENTUM_ITEM_H

#include "../Entities/Player.h"

//Clase interfaz de la que heredan todos los items
class Item {
public:
    virtual void use(Player& player) = 0;
};


#endif //ARGENTUM_ITEM_H
