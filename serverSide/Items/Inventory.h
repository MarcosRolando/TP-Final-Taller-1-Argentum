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
#include "UseReturnData.h"
#include "../Server/PlayerData.hpp"

class ItemTests;
class EntityTests;
class MapTests;
class Game;
class PlayerStats;
class Weapon;
class Player;
class Clothing;
class Item;
class Minichat;
struct Coordinate;


/*Esta clase representa los items que almacena y tiene equipados el jugador*/
class Inventory {
private:
    unsigned int storedItemsAmount{};
    std::vector<std::shared_ptr<Item>> items;
    std::unordered_map<GameType::EquipmentPlace, std::shared_ptr<Clothing>> clothingEquipment;
    std::shared_ptr<Weapon> equippedWeapon;

    friend ItemTests;
    friend EntityTests;
    friend MapTests;

private:
    UseReturnData _manageItemPlacement(GameType::EquipmentPlace equipmentPlace, unsigned int itemPosition);
    void _dropEquippedItems(std::list<std::shared_ptr<Item>>& droppedItems);
    static void _storeNullItemData(std::stringstream& buffer);
    void _restoreDefaultEquipment();
    void _loadInitialInventory(const PlayerData& data);

public:
    explicit Inventory(const PlayerData& data);

    /*Adquiere el shared pointer recibido y lo guarda si hay espacio y retorna
    true. Si no hay espacio o item es null no adquiere el puntero y retorna false*/
    bool addItem(std::shared_ptr<Item>& item);

    /*Elimina el item del inventario de la posicion recibida  y lo retorna,
    dejando el lugar que ocupaba para un nuevo item que quiera ser guardado
    Si no hay un item en la posicion retorna un shared_ptr que almacena null_ptr*/
    std::shared_ptr<Item> removeItem(unsigned int itemPosition);

    /*Elimina el item con el nombre recibido del inventario y lo retorna,
    dejando el lugar que ocupaba para un nuevo item que quiera ser guardado
    Si no hay un item con el nombre recibido retorna un shared_ptr que almacena null_ptr*/
    std::shared_ptr<Item> removeItem(const std::string& itemName);

    /*Usa el item en la posicion indicada, si no hay un item en la posicion no
    hace nada*/
    UseReturnData useItem(Player& player, unsigned int itemPosition);

    /*Retorna el danio generado por el arma dentro del rango de ella
     * Si el target esta fuera del rango del arma retorna 0 de danio*/
    int getWeaponDamage(Coordinate currentPosition, Coordinate target, PlayerStats& stats) const;

    /*Retorna la defensa total provista por la armadura equipada (casco, chest, shield)*/
    unsigned int getDefense();

    /*Retorna una lista con todos los items del iventario, quitandolos del mismo*/
    std::list<std::shared_ptr<Item>> dropAllItems();

    /*Desequipa la ropa de la posicion seleccionada en los equipados y la almacena
     * en el inventario. Si no tiene equipado nada (o sea un default) no hace nada*/
    bool unequip(GameType::EquipmentPlace clothing);

    /*Desequipa el arma  y la almacena en el inventario. Si no tiene equipada un arma
     * (o sea un default) no hace nada*/
    bool unequip();

    /*Almacena en el buffer la informacion de los items equipados del jugador
     * acorde al protocolo*/
    void storeEquippedItems(std::stringstream& buffer) const;

    /*Almacena toda la data relevante que tiene en el inventario/equipado el
     * jugador acorde al protocolo. Se usa para los updates individuales
     * que se envian periodicamente a cada player (para que sepa que tiene
     * equipado en la UI)*/
    void storeAllData(std::stringstream& buffer) const;

    /*Retorna el tipo de arma (Axe, Longsword, etc)*/
    int32_t getWeaponId();

    /*Retorna true si se tiene el item almacenado en el inventario (no equipado),
     * false en caso contrario*/
    bool hasItem(const std::string& itemName);

    /*Almacena en el minichat los nombres de los items que se encuentran en el
     * inventario*/
    void getInventoryNames(Minichat& chat);

    /*Almacena el inventario del player en pData, se usa para el backup del archivo*/
    void getData(PlayerData& pData) const;
};


#endif //ARGENTUM_INVENTORY_H