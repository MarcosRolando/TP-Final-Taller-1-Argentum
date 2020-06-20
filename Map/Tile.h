//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_TILE_H
#define ARGENTUM_TILE_H

#include <memory>
#include <list>
#include "../Items/Item.h"
#include "FloorType.h"
#include "../Entities/Entity.h"

class Tile {
private:
    std::unique_ptr<Entity> entity;
    std::list<std::shared_ptr<Item>> items;
    bool isOccupable;
    FloorType floor;
private:
    void _doMove(Tile&& other) noexcept;
public:
    //Inicializa el tile, dependiendo tel tipo de piso que reciba seteara el
    //tile como ocupable o no ocupable
    explicit Tile(FloorType floor);

    //Constructor por movimiento, intercambia las entities de las tiles
    //El tile se queda con la entity de other, y other con la del tile que
    //llama a la funcion
    Tile(Tile&& other) noexcept;

    Tile& operator=(Tile&& other) noexcept;

    //Intenta agregar la entity al tile
    //Si la posicion es ocupable entonces se apropia
    //del puntero y retorna true, sino no se apropia de de el y retorna false

    //bool addEntity(Entity *received_entity);
    bool addEntity(std::unique_ptr<Entity>&& received_entity);

    //Elimina la entity guardada, habilita la ocupacion del tile por otra
    //entity
    //La funcion no chequea si el tile es ocupable o no debido a FloorType,
    //una llamada a esa funcion en un tile no ocupable lo hara ocupable
    //independientemente del tile
    void removeEntity();

    //Intenta agregar el item al tile, sumandolo a los items ya guardados

    //void addItem(Item *received_item);
    void addItem(std::shared_ptr<Item>&& received_item);

    //Agrega los items recibidos en la lista a los items que contiene el tile
    void addItem(std::list<std::shared_ptr<Item>>&& _items);

    //Elimina uno de los items que se encuentran en el tile y lo retorna}
    //Si no hay ningun item retorna nullptr
    std::shared_ptr<Item> removeItem();

    //Ataca la entidad que se encuentre guardada en el mapa
    //Retorna la cantidad de daño que recibio la entidad atacada, si no hay
    //una entidad retorna 0
    AttackResult attacked(int damage, unsigned int level);

    //Retorna true si almacena un entity que es un target de un monster
    bool hasMonsterTarget() const;

    //Indica si el tile puede ser ocupado por una entity
    //Retorna true si puede, false en otro caso
    bool isAvailable() const;

    //Delega el comportamiento a la entity que guarda, si es que guarda una
    unsigned int list(Player& player, std::list<ProductData>& products);

    //Delega el comportamiento a la entity que guarda, si es que guarda una
    void withdraw(Player& player, const std::string& itemName);

    //Delega el comportamiento a la entity que guarda, si es que guarda una
    void deposit(Player& player, const std::string& itemName);

    //Delega el comportamiento a la entity que guarda, si es que guarda una
    void buy(Player& player, const std::string& itemName);

    //Delega el comportamiento a la entity que guarda, si es que guarda una
    void sell(Player& player, const std::string& itemName);
};


#endif //ARGENTUM_TILE_H
