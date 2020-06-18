//
// Created by agustin on 16/6/20.
//

#ifndef ARGENTUM_SHOP_H
#define ARGENTUM_SHOP_H


#include "Storage.h"
#include "../Player.h"

class Shop {
private:
    float buyingMultiplier;
    float sellingMultiplier;
    Storage storage;
public:

    Shop();

    Shop(const std::unordered_map<std::string, unsigned int>&
         initialItemsAmmounts, float buyingMultiplier, float sellingMultiplier);

    Shop(Shop&& other) noexcept;

    Shop& operator=(Shop&& other) noexcept;

    //Almacena en la lista los items que tiene en venta, los precios
    //almacenados para cada producto fueron modificados utilizando el
    //multiplicador recibido en el constructor
    unsigned int list(std::list<ProductData>& products);

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
