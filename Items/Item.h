//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_ITEM_H
#define ARGENTUM_ITEM_H

#include <string>
#include <memory>
#include "../Config/GameEnums.h"

class ItemTests;

enum EquipmentPlace{
    EQUIPMENT_PLACE_NONE, EQUIPMENT_PLACE_HEAD, EQUIPMENT_PLACE_CHEST, EQUIPMENT_PLACE_WEAPON,
    EQUIPMENT_PLACE_SHIELD
};

class Player;

//Clase interfaz de la que heredan todos los items
//Los items solo tienen sentido en un inventario de un jugador
class Item {
private:
    //El id esta asocioado al tipo de item que es, estos se repiten entre los distintos
    //tipos de items. Ej: Se puede tener un arma y un escudo con el mismo id, pero se
    //diferencian por ser uno un arma y otro un escudo
    GameType::ItemType type;
    const std::string& name;
    //unsigned int price;
    bool isItemInFloor;

    friend ItemTests;

protected:
    int32_t id{};

public:
    //Constructor que copia el nombre recibido en el item para almacenarlo
    Item(GameType::ItemType _type, const std::string& name);

    //Constructor que se apropia del nombre del item
    //Item(std::string&& name, unsigned int price);

    //use debe retornar el lugar en el que debera equiparse el item una vez usado desde
    //un inventario, si debe ser descartado entonces se tiene que retornar INVENTORY_PLACE_NONE
    //Esta funcion retorna en cierta forma el tipo de item que es
    virtual EquipmentPlace use(Player& player);

    const std::string& getName() const;

    virtual bool isGold() const;

    void loadDropItemData(std::stringstream& buffer, uint32_t i, uint32_t j) const;

    void loadEquippedItemData(std::stringstream& buffer);

    void loadTypeAndId(std::stringstream& buffer);

    //Setea el estado del item como tirado en el piso
    void drop();

    //Setea el estado del item como que no esta tirado en el piso
    void grab();

    //Retorna true si esta en el piso, false si fue recogido por alguien (se usa para
    //ver si se tiene que eliminar de la lista de items que guarda game)
    bool isInFloor();

    virtual ~Item() = default;
};


#endif //ARGENTUM_ITEM_H
