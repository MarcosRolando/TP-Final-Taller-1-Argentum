//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_BUY_H
#define ARGENTUM_BUY_H


#include "Event.h"
#include <string>

class Player;

class Buy : public Event {
private:
    Player& player;
    std::string itemName;

public:
    Buy(Player& player, std::string& _itemName);
    void operator()();
};


#endif //ARGENTUM_BUY_H
