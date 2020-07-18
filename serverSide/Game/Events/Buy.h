//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_BUY_H
#define ARGENTUM_BUY_H


#include "Event.h"
#include <string>
#include "../../Map/Coordinate.h"

class Player;

//Clase que se almacena en la cola de eventos cuando un player quiere ejecutar
//el comando de comprar en un tile
class Buy : public Event {
private:
    Player& player;
    std::string itemName;
    Coordinate npcPosition{};

public:
    Buy(Player& player, std::string&& _itemName, Coordinate _npcPosition);

    //Intenta comprar el item con el nombre guardado al entity que se encuentre
    //en la coordenada guardada
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_BUY_H
