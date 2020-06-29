//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_SELL_H
#define ARGENTUM_SELL_H


#include "Event.h"
#include "../../Map/Coordinate.h"


class Player;

class Sell: public Event {
private:
    Player& player;
    Coordinate position;
    std::string itemName;
public:
    Sell(Player& player, const std::string& itemName, Coordinate position);
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_SELL_H
