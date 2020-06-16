//
// Created by agustin on 16/6/20.
//

#ifndef ARGENTUM_SHOP_H
#define ARGENTUM_SHOP_H


#include "Storage.h"

class Shop {
private:
    float buyingMultiplier;
    float sellingMultiplier;
    Storage storage;
public:

    Shop(std::unordered_map<std::string,
            std::list<std::shared_ptr<Item>>>&& initialItems, float buyingMultiplier, float sellingMultiplier);

    //Implementa el comportamiento realizado al pedirle una lista de los items
    //que tiene en venta, por default no hace nada, debe ser reimplementada
    //si la clase hija tiene objetos en venta para listar
    unsigned int list(std::list<ProductData>& products) override;

    //Implementa el comportamiento realizado al intentar el jugador comprar un item
    //con el nombre pasado, por default no hace nada, debe ser reimplementada
    //si la clase hija puede comprar y vender items
    void buy(Player& player, const std::string& itemName) override;

    //Implementa el comportamiento realizado al intentar el jugador vender un item que se
    //encuentra en la posicion pasada, por default no hace nada, debe ser reimplementada
    //si la clase hija puede comprar y vender items
    void sell(Player& player, const std::string& itemName) override;
};


#endif //ARGENTUM_SHOP_H
