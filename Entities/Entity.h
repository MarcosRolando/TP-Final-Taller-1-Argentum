//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_ENTITY_H
#define ARGENTUM_ENTITY_H


#include "../Map/Coordinate.h"
#include <list>

class Entity {
protected:
    Coordinate currentPosition;

public:
    explicit Entity(Coordinate initialPosition);

    //Implementa el comportamiento realizado al ser atacado, por default
    //retorna 0, debe ser modificado en las clases hijas de ser necesario
    virtual unsigned int attacked(unsigned int damage, unsigned int level);

    //Implementa el comportamiento realizado al pedirle una lista de los items
    //que tiene en venta, por default no hace nada, debe ser reimplementada
    //si la clase hija tiene objetos en venta para listar
    virtual void list(std::list<ProductData>& products);

    //Implementa el comportamiento realizado al pedirle uno de los items
    //que tiene guardados, por default no hace nada, debe ser reimplementada
    //si la clase hija puede almacenar y devolver items
    virtual void withdraw(Player& player, const std::string& itemName);

    //Implementa el comportamiento realizado al pedirle que guarde el item que se
    //encuentra en la posicion pasada, por default no hace nada, debe ser reimplementada
    //si la clase hija puede almacenar y devolver items
    virtual void deposit(Player& player, unsigned int itemPosition);

    //Implementa el comportamiento realizado al intentar comprar un item
    //con el nombre pasado, por default no hace nada, debe ser reimplementada
    //si la clase hija puede comprar y vender items
    virtual void buy(Player& player, const std::string& itemName, unsigned int gold);

    //Implementa el comportamiento realizado al intentar vender un item que se
    //encuentra en la posicion pasada, por default no hace nada, debe ser reimplementada
    //si la clase hija puede comprar y vender items
    virtual void sell(Player& player, unsigned int itemPosition);

    //Indica si el Entity va a ser atacado por un monstruo, por default retorna
    //false, las clases que hereden deben reimplementarla si son consideradas
    //targets
    virtual bool isMonsterTarget();

    //Le asigna al jugador la posicion recibida
    void setPosition(Coordinate coordinate);


    //Retorna la posicion en la que quiere estar el jugadoras
    Coordinate getPosition();
};


#endif //ARGENTUM_ENTITY_H
