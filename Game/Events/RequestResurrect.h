//
// Created by agustin on 8/7/20.
//

#ifndef ARGENTUM_REQUESTRESURRECT_H
#define ARGENTUM_REQUESTRESURRECT_H


#include "Event.h"
#include "../../Map/Coordinate.h"

class Player;
class Game;

class RequestResurrect: public Event {
private:
    Player& player;
    Game& game;
    Coordinate selectedPosition;

public:
    RequestResurrect(Player& player, Game& game, Coordinate selectedPosition);
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_REQUESTRESURRECT_H
