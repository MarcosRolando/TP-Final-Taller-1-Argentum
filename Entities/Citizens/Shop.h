//
// Created by agustin on 16/6/20.
//

#ifndef ARGENTUM_SHOP_H
#define ARGENTUM_SHOP_H


#include "Storage.h"

class Player;

class EntityTests;


class Shop {
private:
    float buyingMultiplier{};
    float sellingMultiplier{};
    Storage storage;
    std::unordered_map<std::string, unsigned int> prices;
    std::unordered_set<std::string> acceptedProducts;

    friend EntityTests;

public:

    Shop();

    Shop(const std::unordered_map<std::string, unsigned int>&
         initialItemsAmounts, std::unordered_set<std::string>&& acceptedProducts, float buyingMultiplier, float sellingMultiplier);

    Shop(Shop&& other) noexcept;

    Shop& operator=(Shop&& other) noexcept;

    //Almacena en la lista los items que tiene en venta, los precios
    //almacenados para cada producto fueron modificados utilizando el
    //multiplicador recibido en el constructor
    //unsigned int list(const Player &player, std::list<ProductData>& products);
    void list(Player &player) const;

    //Funcion utilizada cuando el jugador quiere comprar un item, si el jugador no
    //tiene oro suficiente o el item pedido no esta guardado entonces no hace nada,
    //sino
    void buy(Player& player, const std::string& itemName);

    //CAMBIAR COMMENT
    //Implementa el comportamiento realizado al intentar el jugador vender un item que se
    //encuentra en la posicion pasada, por default no hace nada, debe ser reimplementada
    //si la clase hija puede comprar y vender items
    void sell(Player& player, const std::string& itemName);
};


#endif //ARGENTUM_SHOP_H
