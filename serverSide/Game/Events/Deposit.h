//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_DEPOSIT_H
#define ARGENTUM_DEPOSIT_H


#include "Event.h"
#include <string>
#include "../../Map/Coordinate.h"

class Player;

//Clase que se almacena en la cola de eventos cuando un player quiere ejecutar
//el comando de deposit en un tile
class Deposit : public Event {
private:
    Player& player;
    std::string itemName;
    Coordinate npcPosition{};

public:
    Deposit(Player& player, std::string&& _itemName, Coordinate _npcPosition);

    //Intenta depositar el item con el nombre en el entity que se encuentre
    //en la coordenada guardada, pidiendole a map que realice esa accion
    void operator()(ServerProtocol& protocol) override;

};


#endif //ARGENTUM_DEPOSIT_H
