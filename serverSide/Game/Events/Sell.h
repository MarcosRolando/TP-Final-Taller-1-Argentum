//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_SELL_H
#define ARGENTUM_SELL_H


#include "Event.h"
#include "../../Map/Coordinate.h"


class Player;

//Clase que se almacena en la cola de eventos cuando un player quiere ejecutar
//el comando sell
class Sell: public Event {
private:
    Player& player;
    Coordinate position{};
    std::string itemName;
public:
    Sell(Player& player, std::string&& itemName, Coordinate position);

    //Intenta llamar a sell en la posicion guardada en el constructor, pidiendole
    //a map que realice esa accion
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_SELL_H
