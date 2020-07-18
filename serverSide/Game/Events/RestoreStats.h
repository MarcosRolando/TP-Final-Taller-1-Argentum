//
// Created by agustin on 10/7/20.
//

#ifndef ARGENTUM_RESTORESTATS_H
#define ARGENTUM_RESTORESTATS_H


#include "Event.h"
#include "../../Map/Coordinate.h"

class Player;
class Game;

//Clase que se almacena en la cola de eventos cuando un player quiere ejecutar
//el comando heal
class RestoreStats: public Event {
private:
    Game& game;
    Player& player;
    Coordinate target;

public:
    RestoreStats(Game& game, Player& player, Coordinate target);

    //Pide a game que llame a heal para el mapa en la coordenada recibida
    void operator()(ServerProtocol& serverProtocol) override;
};


#endif //ARGENTUM_RESTORESTATS_H
