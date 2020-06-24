//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_WITHDRAW_H
#define ARGENTUM_WITHDRAW_H


#include "Event.h"
#include <string>
#include "../../Map/Coordinate.h"

class Player;

class Withdraw : public Event {
private:
    Player& player;
    std::string itemName;
    Coordinate npcPosition{};

public:
    Withdraw(Player& player, std::string& _itemName, Coordinate _npcPosition);
    void operator()() override;
};

#endif //ARGENTUM_WITHDRAW_H
