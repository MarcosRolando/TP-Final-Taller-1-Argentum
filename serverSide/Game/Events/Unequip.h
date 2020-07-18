//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_UNEQUIP_H
#define ARGENTUM_UNEQUIP_H


#include "Event.h"
#include "../../Items/Defense/Clothing.h"
#include "../../../libs/GameEnums.h"

//Clase que se almacena en la cola de eventos cuando un player quiere desequiparse
//un item
class Unequip : public Event {
private:
    Player& player;
    GameType::EquipmentPlace equipment;

public:
    Unequip(Player& player, GameType::EquipmentPlace equipment);

    //Intenta desequipar el item del lugar recibido en el constructor, si logra
    //hacerlo entonces le comunica a los clientes que ese item ya no se encuentra
    //equipado, agregandolo al protocolo
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_UNEQUIP_H
