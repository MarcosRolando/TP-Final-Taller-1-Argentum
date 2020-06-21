//
// Created by agustin on 8/6/20.
//

#ifndef ARGENTUM_INVENTORY_H
#define ARGENTUM_INVENTORY_H


#include <vector>
#include <memory>
#include <unordered_map>
#include <list>
#include "Item.h"

class Weapon;
class Player;
class Clothing;
class Item;
struct Coordinate;

//Esta clase representa los items que almacena y tiene equipados el jugador
class Inventory {
private:
    unsigned int storedItemsamount;
    std::vector<std::shared_ptr<Item>> items;
    std::unordered_map<EquipmentPlace, std::shared_ptr<Clothing>> clothingEquipment;
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

    //Retorna el danio generado por el arma en el rango de ella
    int getWeaponDamage(Coordinate currentPosition, Coordinate target,
                        unsigned int& currentMana) const;

    //Retorna la defensa total provista por la armadura equipada (casco, chest, shield)
    unsigned int getDefense();

    //Retorna una lista con todos los items del iventario, quitandolos del mismo
    std::list<std::shared_ptr<Item>> dropAllItems();

    void unequip(EquipmentPlace clothing);

    void unequip();

private:
    void _dropEquippedItems(std::list<std::shared_ptr<Item>>& droppedItems);
};


#endif //ARGENTUM_INVENTORY_H
