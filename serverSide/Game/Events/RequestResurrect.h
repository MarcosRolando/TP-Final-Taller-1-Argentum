//
// Created by agustin on 8/7/20.
//

#ifndef ARGENTUM_REQUESTRESURRECT_H
#define ARGENTUM_REQUESTRESURRECT_H


#include "Event.h"
#include "../../Map/Coordinate.h"

class Player;
class Game;

//Clase que se almacena en la cola de eventos cuando un player quiere ejecutar
//el comando resurrect
class RequestResurrect: public Event {
private:
    Player& player;
    Game& game;
    Coordinate selectedPosition{};

public:
    RequestResurrect(Game& game, Player& player, Coordinate selectedPosition);

    //Pide a game que reviva al player, mandandole la coordenada a la que player
    //le hace el pedido, si es resucitado al realizarlo entonces se agrega esta
    //informacion al protocolo para que le llegue a todos los clientes y sepan
    //que el player esta vivo
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_REQUESTRESURRECT_H
