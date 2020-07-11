//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_DEPOSIT_H
#define ARGENTUM_DEPOSIT_H


#include "Event.h"
#include <string>
#include "../../Map/Coordinate.h"

class Player;

class Deposit : public Event {
private:
    Player& player;
    std::string itemName;
    Coordinate npcPosition{};

public:
    Deposit(Player& player, std::string&& _itemName, Coordinate _npcPosition);
    void operator()(ServerProtocol& protocol) override;

};


#endif //ARGENTUM_DEPOSIT_H
