//
// Created by agustin on 13/7/20.
//

#ifndef ARGENTUM_GETINVENTORYNAMES_H
#define ARGENTUM_GETINVENTORYNAMES_H


#include "Event.h"

class Player;

class GetInventoryNames: public Event {
private:
    Player& player;

public:
    GetInventoryNames(Player& player);
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_GETINVENTORYNAMES_H
