//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_UNEQUIP_H
#define ARGENTUM_UNEQUIP_H


#include "Event.h"
#include "../../Items/Defense/Clothing.h"
#include "../../Config/GameEnums.h"

class Unequip : public Event {
private:
    Player& player;
    GameType::EquipmentPlace equipment;

public:
    Unequip(Player& player, GameType::EquipmentPlace equipment);
    explicit Unequip(Player& player);
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_UNEQUIP_H
