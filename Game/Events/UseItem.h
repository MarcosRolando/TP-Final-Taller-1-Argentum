//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_USEITEM_H
#define ARGENTUM_USEITEM_H


#include "Event.h"

class Player;

class UseItem: Event {
private:
    Player& player;
    int position;
public:
    UseItem(Player& player, int position);
    void operator()() override;
};


#endif //ARGENTUM_USEITEM_H
