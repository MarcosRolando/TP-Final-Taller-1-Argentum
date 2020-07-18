//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_ATTACK_H
#define ARGENTUM_ATTACK_H


#include "Event.h"
#include "../../Map/Coordinate.h"
#include "../../../libs/GameEnums.h"

class Entity;

//Clase que se almacena en la cola de eventos cuando se quiere que un entity
//ataque a un tile
class Attack : public Event {
private:
    Entity& entity;
    Coordinate target{};

public:
    Attack(Entity& _entity, Coordinate _target);

    //Realiza el ataque y de ser necesario almacena el evento en el protocolo
    //para comunicarselo a los clientes
    void operator()(ServerProtocol& protocol) override;

private:
    GameType::Direction _attackDirection(Coordinate attackerPosition) const;
};


#endif //ARGENTUM_ATTACK_H
