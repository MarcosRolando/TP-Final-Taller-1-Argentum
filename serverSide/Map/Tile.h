//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_TILE_H
#define ARGENTUM_TILE_H

#include <memory>
#include <list>
#include "../../libs/GameEnums.h"
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
    explicit Tile(bool isOccupable, bool isFromCity, GameType::FloorType floor,
                  GameType::Structure structure, std::shared_ptr<Entity>&& initialEntity);

    //El tile se queda con la entity de other y setea la de other en nullptr,
    //actualizando tambien el estado de si es ocupable o no en ambos tiles
    void moveEntity(Tile& otherTile, Coordinate position);

    //Intenta agregar la entity al tile
    //Si la posicion es ocupable entonces se apropia del puntero
    void addEntity(std::shared_ptr<Entity>&& received_entity);

    //Elimina la entity guardada, habilita la ocupacion del tile por otra
    //entity
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
    //una entidad retorna 0, el booleano indica si se realizo o no el ataque al tile,
    //valiendo true si se realizo, false en otro caso (que no haya un entity no hace
    //necesariamente que sea false)
    std::pair<AttackResult, bool> attacked(int damage, unsigned int level, bool isAPlayer);

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

    //Guarda en el buffer el entity almacenado en el tile, junto con el tipo de
    //piso y la estructura almacenadas
    void operator>>(std::stringstream & mapBuffer) const;

    //Retorna un puntero al item que se debe mostrar en el mapa
    const Item* peekShowedItemData();

    //Le pide al entity guardado en el tile que restaure la vida y el mana del
    //player recibido, si no hay un entity entonces no hace nada
    void requestRestore(Player& player);
};


#endif //ARGENTUM_TILE_H
