//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_USEITEM_H
#define ARGENTUM_USEITEM_H


#include "Event.h"

class Player;

//Clase que se almacena en la cola de eventos cuando un player quiere usar
//un item
class UseItem : public Event {
private:
    Player& player;
    int position;

public:
    UseItem(Player& player, int position);

    //Intenta usar el item del lugar recibido en el constructor, en caso de ser
    //necesario, le comuinica al resto de los clientes si algun (y cual) item fue equipado
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_USEITEM_H
