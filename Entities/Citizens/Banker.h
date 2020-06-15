//
// Created by agustin on 15/6/20.
//

#ifndef ARGENTUM_BANKER_H
#define ARGENTUM_BANKER_H


#include "../Entity.h"

class Banker: Entity {
private:
    Storage storage;

public:
    //Implementa el comportamiento realizado al pedirle una lista de los items
    //que tiene en venta, por default no hace nada, debe ser reimplementada
    //si la clase hija tiene objetos en venta para listar
    void list(std::list<ProductData>& products) override;

    //Implementa el comportamiento realizado al pedirle uno de los items
    //que tiene guardados, por default no hace nada, debe ser reimplementada
    //si la clase hija puede almacenar y devolver items
    void withdraw(Player& player, const std::string& itemName) override;

    //Implementa el comportamiento realizado al pedirle que guarde el item que se
    //encuentra en la posicion pasada, por default no hace nada, debe ser reimplementada
    //si la clase hija puede almacenar y devolver items
    void deposit(Player& player, unsigned int itemPosition) override;
};


#endif //ARGENTUM_BANKER_H
