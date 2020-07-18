//
// Created by agustin on 13/7/20.
//

#ifndef ARGENTUM_GETINVENTORYNAMES_H
#define ARGENTUM_GETINVENTORYNAMES_H


#include "Event.h"

class Player;

//Clase que se almacena en la cola de eventos cuando un player quiere ejecutar
//el comando inventory
class GetInventoryNames: public Event {
private:
    Player& player;

public:
    explicit GetInventoryNames(Player& player);

    //Guarda en el minichat del player almacenado mensajes que indican el nombre
    //de cada item del inventario junto a la posicion del inventario en el que
    //este se encuentra. De la forma posicion: Nombre
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_GETINVENTORYNAMES_H
