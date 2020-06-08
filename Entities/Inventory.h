//
// Created by agustin on 8/6/20.
//

#ifndef ARGENTUM_INVENTORY_H
#define ARGENTUM_INVENTORY_H


#include <vector>
#include <memory>
#include "../Items/Item.h"
#include "Player.h"

class Inventory {
private:
    Player& player;
    unsigned int storedItemsAmmount;
    std::vector<std::shared_ptr<Item>> items;
public:
    Inventory(Player& player);

    //Adquiere el shared pointer recibido y lo guarda si hay espacio y retorna
    //true. Si no hay espacio o item es null no adquiere el puntero y retorna false
    bool addItem(std::shared_ptr<Item>&& item);

    //Elimina el item del inventario de la posicion recibida  y lo retorna,
    //dejando el lugar que ocupaba para un nuevo item que quiera ser guardado
    //Si no hay un item en la posicion retorna un shared_ptr que almacena null_ptr
    std::shared_ptr<Item> removeItem(unsigned int itemPosition);

    //Usa el item en la posicion indicada, si no hay un item en la posicion no
    //hace nada
    void useItem(unsigned int itemPosition);

    /*
    //Retorna el tamanio del inventario
    unsigned int getSize();
    */
};


#endif //ARGENTUM_INVENTORY_H
