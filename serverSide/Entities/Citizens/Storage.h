//
// Created by agustin on 15/6/20.
//

#ifndef ARGENTUM_STORAGE_H
#define ARGENTUM_STORAGE_H

#include <string>
#include <unordered_map>
#include <list>
#include <utility>
#include <memory>
#include "../../Server/PlayerData.hpp"

class Item;
class Player;

class EntityTests;

/*Clase utilizada para guardar instancias de items, se guardan las instancias
y no cantidades de cada item ya que de esa forma no se debe estar creando y
copiando cada vez que se retira algun item. Esto permite ademas extensibilidad
ya que se podria agregar a cada item por separado modificadores y estos quedarian
guardados en la instancia*/

/*Cualquier tipo de item que sea guardado 0 veces no tiene un lugar en el unordered_map*/

class Storage {
private:
    int32_t storedGold;
    std::unordered_map<std::string, std::list<std::shared_ptr<Item>>> storedItems;

    friend EntityTests;

private:
    static void _addAmmountMessageToPlayer(Player& player, const std::string& itemName,
                                    int concatenatedNumber);

public:
    Storage();

    Storage(Storage&& other) noexcept;

    Storage& operator=(Storage&& other) noexcept;

    explicit Storage(const std::unordered_map<std::string, unsigned int>&
                     initialItemsAmounts, unsigned int gold);

    /*Almacena el item, apropiandose de el.
    Retorna true si cambio la cantidad de items guardados, sino retorna false
    La cantidad cambia si se recibe algo que no sea oro*/
    bool storeItem(std::shared_ptr<Item>&& item);

    /*Intenta pasar el item pedido de Storage a Player, si el item no existe o
    el player no tiene espacio entonces no hace nada
    Retorna true si cambio la cantidad de items que guarda, sino retorna false
    La cantidad cambia si se saca algo que no sea oro*/
    bool retreiveItem(const std::string& itemName, Player& player);

    /*Agrega en el minichat del player la lista con los items disponibles y su
     * precio, la usan los vendedores*/
    void getStorageData(Player& player, const std::unordered_map<std::string,
                        unsigned int>& prices, float priceMultiplier) const;

    /*Agrega en el minichat del player la lista con los items disponibles,
     * la usa el banker*/
    void getStorageData(Player& player) const;

    /*Indica si el item con el nombre indicado se encuentra guardado*/
    bool isItemAvailable(const std::string& itemName) const;

    /*Aumenta la cantidad de oro guardado en el storage*/
    void increaseGoldReserves(int amount);

    /*Disminuye la cantidad de oro guardado en el storage*/
    bool decreaseGoldReserves(int amount);

    /*Retorna en el struct playerData los datos de los items que el player
     * tiene guardados*/
    void getPlayerData(PlayerData& playerData) const;
};


#endif //ARGENTUM_STORAGE_H
