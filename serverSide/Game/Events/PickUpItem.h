//
// Created by agustin on 6/7/20.
//

#ifndef ARGENTUM_PICKUPITEM_H
#define ARGENTUM_PICKUPITEM_H


#include "Event.h"

class Game;
class Player;
class ServerProtocol;

//Clase que se almacena en la cola de eventos cuando un player quiere ejecutar
//el comando pickUp
class PickUpItem: public Event {
private:
    Game& game;
    Player& player;

public:
    PickUpItem(Game& game, Player& player);

    //Le dice a game que el player quiere agarrar el item que se encuentra en
    //su posicion, si lo logra entonces manda al cliente el mensaje necesario:
    //Manda que se debe destruir el item de esa posicion si es que ya no quedan
    //mas items, sino manda que se debe crear el item que se quiere mostrar en
    //esa posicion
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_PICKUPITEM_H
