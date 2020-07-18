//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_MOVE_H
#define ARGENTUM_MOVE_H


#include "Event.h"
#include "../../Map/Coordinate.h"
#include "../../../libs/GameEnums.h"

class Game;
class Entity;

//Clase que se almacena en la cola de eventos cuando un entity quiere concretar su
//desplazamiento en alguna direccion
class Move: public Event {
private:
    Game& game;
    Entity& entity;
    GameType::Direction moveDirection;

public:
    Move(Game& _game, Entity& _entity, GameType::Direction moveDirection);

    //Intenta mover el entity guardado en la direccion recibida en el constructor,
    //pasandola inmediatamente al tile si es que esta disponible para el entity,
    //empezando asi su desplazamiento "visual" hacia este
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_MOVE_H
