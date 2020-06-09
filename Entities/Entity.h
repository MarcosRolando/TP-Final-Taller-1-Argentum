//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_ENTITY_H
#define ARGENTUM_ENTITY_H


#include "../Map/Coordinate.h"

class Entity {
protected:
    Coordinate currentPosition;

public:
    explicit Entity(Coordinate initialPosition);

    //Implementa el comportamiento realizado al ser atacado
    virtual unsigned int attacked(unsigned int damage, unsigned int level) = 0;

    //Indica si el Entity va a ser atacado por un monstruo, por default retorna
    //false, las clases que hereden deben reimplementarla si son consideradas
    //targets
    virtual bool isMonsterTarget();

    //Le asigna al jugador la posicion recibida
    void setPosition(Coordinate coordinate);


    //Retorna la posicion en la que quiere estar el jugador
    Coordinate getPosition();
};


#endif //ARGENTUM_ENTITY_H
