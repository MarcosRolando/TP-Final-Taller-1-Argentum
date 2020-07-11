//
// Created by agustin on 10/7/20.
//

#ifndef ARGENTUM_RESTORESTATS_H
#define ARGENTUM_RESTORESTATS_H


#include "Event.h"
#include "../../Map/Coordinate.h"

class Player;
class Game;

class RestoreStats: public Event {
private:
    Game& game;
    Player& player;
    Coordinate target;

public:
    RestoreStats(Game& game, Player& player, Coordinate target);
    void operator()(ServerProtocol& serverProtocol) override;
};


#endif //ARGENTUM_RESTORESTATS_H
