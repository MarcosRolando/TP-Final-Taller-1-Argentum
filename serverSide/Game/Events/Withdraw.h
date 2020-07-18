//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_WITHDRAW_H
#define ARGENTUM_WITHDRAW_H


#include "Event.h"
#include <string>
#include "../../Map/Coordinate.h"

class Player;

//Clase que se almacena en la cola de eventos cuando un player quiere ejecutar
//el comando withdraw
class Withdraw : public Event {
private:
    Player& player;
    std::string itemName;
    Coordinate npcPosition{};

public:
    Withdraw(Player& player, std::string&& _itemName, Coordinate _npcPosition);

    //Intenta llamar a withdraw en la posicion guardada en el constructor, pidiendole
    //a map que realice esa accion
    void operator()(ServerProtocol& protocol) override;
};

#endif //ARGENTUM_WITHDRAW_H
