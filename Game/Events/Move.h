//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_MOVE_H
#define ARGENTUM_MOVE_H


#include "Event.h"
#include "../../Map/Coordinate.h"

class Game;
class Player;

class Move: public Event {
private:
    Game& game;
    Player& player;
    Coordinate destination{};

public:
    Move(Game& _game, Player& _player, Coordinate _destination);
    void operator()() override;
};


#endif //ARGENTUM_MOVE_H
