//
// Created by agustin on 8/6/20.
//

#ifndef ARGENTUM_INVENTORY_H
#define ARGENTUM_INVENTORY_H


#include <vector>
#include <memory>
#include <unordered_map>
#include "Item.h"
#include "../Entities/Player.h"
#include "Defense/Clothing.h"


class Inventory {
private:
    unsigned int storedItemsAmmount;
    std::vector<std::shared_ptr<Item>> items;
    std::unordered_map<EquipmentPlace, std::shared_ptr<Clothing>> equipment;
private:
    void manageItemPlacement(EquipmentPlace equipmentPlace, unsigned int itemPosition);

public:
    Inventory();

    //Adquiere el shared pointer recibido y lo guarda si hay espacio y retorna
    //true. Si no hay espacio o item es null no adquiere el puntero y retorna false
    bool addItem(std::shared_ptr<Item>&& item);

    //Elimina el item del inventario de la posicion recibida  y lo retorna,
    //dejando el lugar que ocupaba para un nuevo item que quiera ser guardado
    //Si no hay un item en la posicion retorna un shared_ptr que almacena null_ptr
    std::shared_ptr<Item> removeItem(unsigned int itemPosition);

    //Usa el item en la posicion indicada, si no hay un item en la posicion no
    //hace nada
    void useItem(Player& player, unsigned int itemPosition);
};


#endif //ARGENTUM_INVENTORY_H
