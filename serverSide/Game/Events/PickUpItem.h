//
// Created by agustin on 6/7/20.
//

#ifndef ARGENTUM_PICKUPITEM_H
#define ARGENTUM_PICKUPITEM_H


#include "Event.h"

class Game;
class Player;
class ServerProtocol;

class PickUpItem: public Event {
private:
    Game& game;
    Player& player;

public:
    PickUpItem(Game& game, Player& player);
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_PICKUPITEM_H
