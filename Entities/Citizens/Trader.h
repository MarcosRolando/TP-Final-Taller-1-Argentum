//
// Created by agustin on 15/6/20.
//

#ifndef ARGENTUM_TRADER_H
#define ARGENTUM_TRADER_H


#include "Storage.h"
#include "../Entity.h"

class Trader: Entity {
private:
    Storage storage;
public:
    //Implementa el comportamiento realizado al pedirle una lista de los items
    //que tiene en venta, por default no hace nada, debe ser reimplementada
    //si la clase hija tiene objetos en venta para listar
    void list(std::list<ProductData>& products) override;

    //Implementa el comportamiento realizado al intentar comprar un item
    //con el nombre pasado, por default no hace nada, debe ser reimplementada
    //si la clase hija puede comprar y vender items
    void buy(Player& player, const std::string& itemName, unsigned int gold) override;

    //Implementa el comportamiento realizado al intentar vender un item que se
    //encuentra en la posicion pasada, por default no hace nada, debe ser reimplementada
    //si la clase hija puede comprar y vender items
    void sell(Player& player, unsigned int itemPosition) override;
};


#endif //ARGENTUM_TRADER_H
