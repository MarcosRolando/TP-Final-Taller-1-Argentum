//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_TILE_H
#define ARGENTUM_TILE_H

#include <memory>
#include <list>
#include "../Config/GameEnums.h"
#include "../Entities/Entity.h"
#include "../Items/ItemData.h"

class MapTests;
class Item;
struct AttackResult;
struct ProductData;
class Player;

class Tile {
private:
    std::shared_ptr<Entity> entity;
    std::list<std::shared_ptr<Item>> items;
    bool isOccupable{};
    bool isFromCity;
    GameType::FloorType floor;
    GameType::Structure structure{GameType::Structure::TREE};

    friend MapTests;

public:
    //Inicializa el tile, dependiendo tel tipo de piso que reciba seteara el
    //tile como ocupable o no ocupable
    explicit Tile(bool isOccupable, bool isFromCity, GameType::FloorType floor,
                  GameType::Structure structure, std::shared_ptr<Entity>&& initialEntity);

    //El tile se queda con la entity de other y setea la de other en nullptr
    void moveEntity(Tile& otherTile, Coordinate position);

    //Intenta agregar la entity al tile
    //Si la posicion es ocupable entonces se apropia
    //del puntero y retorna true, sino no se apropia de de el y retorna false
    void addEntity(std::shared_ptr<Entity>&& received_entity);

    //Elimina la entity guardada, habilita la ocupacion del tile por otra
    //entity
    //La funcion no chequea si el tile es ocupable o no debido a FloorType,
    //una llamada a esa funcion en un tile no ocupable lo hara ocupable
    //independientemente del tile
    void removeEntity();

    //Intenta agregar el item al tile, sumandolo a los items ya guardados
    void addItem(std::shared_ptr<Item>&& received_item);

    //Agrega los items recibidos en la lista a los items que contiene el tile
    void addItem(std::list<std::shared_ptr<Item>>&& _items);

    //Elimina uno de los items que se encuentran en el tile y lo retorna}
    //Si no hay ningun item retorna nullptr
    std::shared_ptr<Item> removeItem();

    //Ataca la entidad que se encuentre guardada en el mapa
    //Retorna la cantidad de daño que recibio la entidad atacada, si no hay
    //una entidad retorna 0
    AttackResult attacked(int damage, unsigned int level, bool isAPlayer);

    //Retorna true si almacena un entity que es un target de un monster
    bool hasMonsterTarget() const;

    //Indica si el tile puede ser ocupado por una entity
    //Retorna true si puede, false en otro caso
    bool isAvailable() const;

    //Delega el comportamiento a la entity que guarda, si es que guarda una
    //void list(Player& player, std::list<ProductData>& products);
    void list(Player& player);

    //Delega el comportamiento a la entity que guarda, si es que guarda una
    void withdraw(Player& player, const std::string& itemName);

    //Delega el comportamiento a la entity que guarda, si es que guarda una
    void deposit(Player& player, const std::string& itemName);

    //Delega el comportamiento a la entity que guarda, si es que guarda una
    void buy(Player& player, const std::string& itemName);

    //Delega el comportamiento a la entity que guarda, si es que guarda una
    void sell(Player& player, const std::string& itemName);

    //Retorna si es de una city
    bool isInCity() const;

    void operator>>(std::stringstream & mapBuffer) const;

    //Guarda el tipo del item y el id del item a mostrar, si no hay items en el
    //tile guarda -1 en el lugar del id (second)
    Item* peekShowedItemData();

    void requestRestore(Player& player);
};


#endif //ARGENTUM_TILE_H
