//
// Created by agustin on 14/7/20.
//

#ifndef ARGENTUM_MODIFYPLAYERMOVEMENT_H
#define ARGENTUM_MODIFYPLAYERMOVEMENT_H


#include "Event.h"
#include "../../../libs/GameEnums.h"

class Player;

//Clase que se almacena en la cola de eventos cuando un player quiere desplazarse
//en alguna direccion
class ModifyPlayerMovement: public Event {
private:
    Player& player;
    GameType::Direction direction{};
    bool continuesMovement;

public:
    //Constructor que le indica a movement que se debe empezar a mover en la direccion
    //recibida
    explicit ModifyPlayerMovement(Player& player, GameType::Direction direction);

    //constructor que le indica a movement que debe dejar de moverse
    explicit ModifyPlayerMovement(Player& player);

    //Guarda el proximo estado de movimiento para que sea ejecutado una vez que
    //termine de realizar el movimiento que se este realizando en el momento
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_MODIFYPLAYERMOVEMENT_H
