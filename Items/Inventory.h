//
// Created by agustin on 8/6/20.
//

#ifndef ARGENTUM_INVENTORY_H
#define ARGENTUM_INVENTORY_H


#include <vector>
#include <memory>
#include <unordered_map>
#include "Item.h"
//#include "../Entities/Player.h"
#include "Defense/Clothing.h"
#include "Attack/Weapon.h"

class Player;

//Esta clase representa los items que almacena y tiene equipados el jugador
class Inventory {
private:
    unsigned int storedItemsamount;
    std::vector<std::shared_ptr<Item>> items;
    std::unordered_map<EquipmentPlace, std::shared_ptr<Clothing>> clothingEequipment;
    std::shared_ptr<Weapon> equippedWeapon;

private:
    void _manageItemPlacement(EquipmentPlace equipmentPlace, unsigned int itemPosition);

public:
    Inventory();

    //Adquiere el shared pointer recibido y lo guarda si hay espacio y retorna
    //true. Si no hay espacio o item es null no adquiere el puntero y retorna false
    bool addItem(std::shared_ptr<Item>&& item);

    //Elimina el item del inventario de la posicion recibida  y lo retorna,
    //dejando el lugar que ocupaba para un nuevo item que quiera ser guardado
    //Si no hay un item en la posicion retorna un shared_ptr que almacena null_ptr
    std::shared_ptr<Item> removeItem(unsigned int itemPosition);

    //Elimina el item con el nombre recibido del inventario y lo retorna,
    //dejando el lugar que ocupaba para un nuevo item que quiera ser guardado
    //Si no hay un item con el nombre recibido retorna un shared_ptr que almacena null_ptr
    std::shared_ptr<Item> removeItem(const std::string& itemName);

    //Usa el item en la posicion indicada, si no hay un item en la posicion no
    //hace nada
    void useItem(Player& player, unsigned int itemPosition);

    const Weapon& getEquippedWeapon() const;
};


#endif //ARGENTUM_INVENTORY_H