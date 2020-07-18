//
// Created by agustin on 5/7/20.
//

#ifndef ARGENTUM_NOTIFYDEATH_H
#define ARGENTUM_NOTIFYDEATH_H


#include "Event.h"

#include <sstream>

class Player;

//Clase que se almacena en la cola de eventos para notificarle a los clientes que
//un player murio, por lo que ahora es un fantasma
class NotifyDeath: public Event {
private:
    const Player& player;

private:
    void _appendUnequipMessages(std::stringstream& data);

public:
    explicit NotifyDeath(const Player& player);

    //Guarda en el protocolo los mensajes de muerte y desequipamiento de items,
    //ademas del equipamiento de los items default, para que se envie a todos los
    //clientes
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_NOTIFYDEATH_H
