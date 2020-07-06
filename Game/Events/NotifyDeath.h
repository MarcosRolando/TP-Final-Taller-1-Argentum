//
// Created by agustin on 5/7/20.
//

#ifndef ARGENTUM_NOTIFYDEATH_H
#define ARGENTUM_NOTIFYDEATH_H


#include "Event.h"

class Player;

//Clase utilizada para notificar a todos los clientes de la muerte de un jugador
class NotifyDeath: public Event {
private:
    const Player& player;

public:
    explicit NotifyDeath(const Player& player);
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_NOTIFYDEATH_H
