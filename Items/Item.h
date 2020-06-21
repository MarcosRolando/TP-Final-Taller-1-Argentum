//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_ITEM_H
#define ARGENTUM_ITEM_H

#include <string>
#include <memory>

enum EquipmentPlace{
    EQUIPMENT_PLACE_NONE, EQUIPMENT_PLACE_HEAD, EQUIPMENT_PLACE_CHEST, EQUIPMENT_PLACE_WEAPON,
    EQUIPMENT_PLACE_SHIELD
};

enum ItemType {
    ITEM_TYPE_GOLD, ITEM_TYPE_WEAPON, ITEM_TYPE_CLOTHING, ITEM_TYPE_POTION
};

class Player;

//Clase interfaz de la que heredan todos los items
//Los items solo tienen sentido en un inventario de un jugador
class Item {
private:
    //El id esta asocioado al tipo de item que es, estos se repiten entre los distintos
    //tipos de items. Ej: Se puede tener un arma y un escudo con el mismo id, pero se
    //diferencian por ser uno un arma y otro un escudo

    unsigned int id;
    ItemType type;
    const std::string& name;
    unsigned int price;
public:
    //Constructor que copia el nombre recibido en el item para almacenarlo
    Item(const std::string& name, unsigned int price);

    //Constructor que se apropia del nombre del item
    //Item(std::string&& name, unsigned int price);

    //use debe retornar el lugar en el que debera equiparse el item una vez usado desde
    //un inventario, si debe ser descartado entonces se tiene que retornar INVENTORY_PLACE_NONE
    //Esta funcion retorna en cierta forma el tipo de item que es
    virtual EquipmentPlace use(Player& player);

    const std::string& getName() const;

    unsigned int getPrice() const;

    virtual bool isGold() const;

    virtual ~Item() = default;
};


#endif //ARGENTUM_ITEM_H
