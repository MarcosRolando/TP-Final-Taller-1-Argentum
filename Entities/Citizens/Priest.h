//
// Created by agustin on 15/6/20.
//

#ifndef ARGENTUM_PRIEST_H
#define ARGENTUM_PRIEST_H


#include "Shop.h"
#include "../Entity.h"

class EntityTests;

class Priest: public Entity {
private:
    Shop shop;

    friend EntityTests;

public:
    explicit Priest(Coordinate initialPosition);

    //Implementa el comportamiento realizado al pedirle una lista de los items
    //que tiene en venta, por default no hace nada, debe ser reimplementada
    //si la clase hija tiene objetos en venta para listar
    //unsigned int list(const Player &player, std::list<ProductData>& products) override;
    void list(Player &player) override;

    //Implementa el comportamiento realizado al intentar el jugador comprar un item
    //con el nombre pasado, por default no hace nada, debe ser reimplementada
    //si la clase hija puede comprar y vender items
    void buy(Player& player, const std::string& itemName) override;

    //Implementa el comportamiento realizado al intentar el jugador vender un item que se
    //encuentra en la posicion pasada, por default no hace nada, debe ser reimplementada
    //si la clase hija puede comprar y vender items
    void sell(Player& player, const std::string& itemName) override;
};


#endif //ARGENTUM_PRIEST_H
