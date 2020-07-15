//
// Created by agustin on 14/7/20.
//

#ifndef ARGENTUM_MODIFYPLAYERMOVEMENT_H
#define ARGENTUM_MODIFYPLAYERMOVEMENT_H


#include "Event.h"
#include "../../../libs/GameEnums.h"

class Player;

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

    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_MODIFYPLAYERMOVEMENT_H
