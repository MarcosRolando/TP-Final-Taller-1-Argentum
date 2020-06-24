//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_DROP_H
#define ARGENTUM_DROP_H


#include "Event.h"

#include <string>

class Player;

class Drop: public Event {
private:
    Player& player;
    unsigned int position;
public:
    Drop(Player& player, unsigned int position);
    void operator()() override;
};


#endif //ARGENTUM_DROP_H
