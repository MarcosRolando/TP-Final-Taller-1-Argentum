//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_BUY_H
#define ARGENTUM_BUY_H


#include "Event.h"
#include <string>
#include "../../Map/Coordinate.h"

class Player;

class Buy : public Event {
private:
    Player& player;
    std::string itemName;
    Coordinate npcPosition{};

public:
    Buy(Player& player, std::string& _itemName, Coordinate _npcPosition);
    void operator()() override;
};


#endif //ARGENTUM_BUY_H
