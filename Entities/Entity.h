//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_ENTITY_H
#define ARGENTUM_ENTITY_H


#include "../Map/Coordinate.h"
#include "../Items/Product.h"
#include <list>

class Entity {
protected:
    Coordinate currentPosition;

public:
    explicit Entity(Coordinate initialPosition);

    //Implementa el comportamiento realizado al ser atacado, por default
    //retorna 0, debe ser modificado en las clases hijas de ser necesario
    virtual unsigned int attacked(unsigned int damage, unsigned int level);

    //Implementa el comportamiento realizado al ser atacado, por default
    //retorna 0, debe ser modificado en las clases hijas de ser necesario
    virtual void list(std::list<ProductData>);

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
