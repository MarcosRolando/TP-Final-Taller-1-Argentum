//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_LIST_H
#define ARGENTUM_LIST_H


#include "Event.h"
#include <string>
#include "../../Map/Coordinate.h"

class Player;

class List : public Event {
private:
    Player& player;
    Coordinate npcPosition{};

public:
    List(Player& player, Coordinate _npcPosition);
    void operator()() override;
};


#endif //ARGENTUM_LIST_H
