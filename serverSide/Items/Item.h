//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_ITEM_H
#define ARGENTUM_ITEM_H

#include <string>
#include <memory>
#include "../../libs/GameEnums.h"
#include "UseReturnData.h"

class ItemTests;
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

    friend ItemTests;

protected:
    int32_t id{};

public:
    Item(GameType::ItemType _type, const std::string& name);

    /*use debe retornar el lugar en el que debera equiparse el item una vez usado desde
    un inventario, si debe ser descartado entonces se tiene que retornar INVENTORY_PLACE_NONE
    Esta funcion retorna en cierta forma el tipo de item que es*/
    virtual GameType::EquipmentPlace use(Player& player);

    /*Retorna el nombre del item (viene asignado desde el archivo de config)*/
    const std::string& getName() const;

    /*Esta implementada como false, el unico que la reimplementa es gold que
     * retorna true*/
    virtual bool isGold() const;

    /*Carga en el buffer la informacion correspondiente al item acorde
     * al protocolo, esta funcion se usa cuando un nuevo player se conecta
     * al juego*/
    void loadDropItemData(std::stringstream& buffer, int32_t i, int32_t j) const;

    /*Carga en el buffer la infromacion corresopndiente al item equipado
     * acorde al protocolo, esta funcion se usa cuando un nuevo player
     * se conecta al juego*/
    void loadEquippedItemData(std::stringstream& buffer);

    /*Carga en el buffer el tipo de item y su id (es decir si es un arma cual seria,
     * o si es ropa cual seria. La usa el inventario para el mensaje individual
     * de cada player (este mensaje es para la UI personal, es decir, no para el mapa)*/
    void loadTypeAndId(std::stringstream& buffer);

    virtual ~Item() = default;

    /*Retorna el tipo particular del item (si es una weapon retornaria que tipo
     * de weapon, lo mismo si fuera un chest o un shield)*/
    int32_t getId();

    /*Retorna la clase del item (si es una weapon, shield, chest, etc)*/
    GameType::ItemType getType();
};


#endif //ARGENTUM_ITEM_H
