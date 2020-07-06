//
// Created by agustin on 5/7/20.
//

#ifndef ARGENTUM_NOTIFYDEATH_H
#define ARGENTUM_NOTIFYDEATH_H


#include "Event.h"

#include <sstream>

class Player;

//Clase utilizada para notificar a todos los clientes de la muerte de un jugador
class NotifyDeath: public Event {
private:
    const Player& player;

private:
    void _appendUnequipMessages(std::stringstream& data);

public:
    explicit NotifyDeath(const Player& player);
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_NOTIFYDEATH_H
