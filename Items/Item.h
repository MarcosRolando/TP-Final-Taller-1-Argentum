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

class Player;

//Clase interfaz de la que heredan todos los items
//Los items solo tienen sentido en un inventario de un jugador
class Item {
private:
    //unsigned int id;
    std::string name;
    unsigned int price;
public:
    //Constructor que copia el nombre recibido en el item para almacenarlo
    explicit Item(const std::string& name, unsigned int price = 0);

    //Constructor que se apropia del nombre del item
    Item(std::string&& name, unsigned int price);

    //use debe retornar el lugar en el que debera equiparse el item una vez usado desde
    //un inventario, si debe ser descartado entonces se tiene que retornar INVENTORY_PLACE_NONE
    //Esta funcion retorna en cierta forma el tipo de item que es
    virtual EquipmentPlace use(Player& player);

    const std::string& getName() const;

    unsigned int getPrice() const;

    /*
    //Retorna una instancia del tipo de item, debe implementarse para cada
    //item final
    virtual std::shared_ptr<Item> getInstance() = 0;
    */

    virtual ~Item() = default;
};


#endif //ARGENTUM_ITEM_H
