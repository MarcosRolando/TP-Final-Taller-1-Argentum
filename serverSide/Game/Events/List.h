//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_LIST_H
#define ARGENTUM_LIST_H


#include "Event.h"
#include <string>
#include "../../Map/Coordinate.h"

class Player;

//Clase que se almacena en la cola de eventos cuando un player quiere ejecutar
//el comando list
class List : public Event {
private:
    Player& player;
    Coordinate npcPosition{};

public:
    List(Player& player, Coordinate _npcPosition);

    //Intenta llamar a list en la posicion guardada en el constructor
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_LIST_H
