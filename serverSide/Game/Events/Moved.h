//
// Created by agustin on 29/6/20.
//

#ifndef ARGENTUM_MOVED_H
#define ARGENTUM_MOVED_H


#include "Event.h"
#include "../../../libs/GameEnums.h"

#include <cstdint>

class Entity;
class ServerProtocol;

//Clase que se almacena en la cola de eventos para notificarle a los clientes que
//un entity se desplazo
class Moved: public Event {
private:
    Entity& entity;
    GameType::Direction direction;
    int32_t displacement;

public:
    Moved(Entity& entity, GameType::Direction direction, int32_t displacement);

    //Almacena en el protocolo el mensaje del desplazamiento de un entity para
    //comunicarselo a todos los clientes
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_MOVED_H
