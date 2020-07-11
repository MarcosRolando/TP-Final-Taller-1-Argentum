//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_MOVE_H
#define ARGENTUM_MOVE_H


#include "Event.h"
#include "../../Map/Coordinate.h"
#include "../../Config/GameEnums.h"

class Game;
class Entity;

class Move: public Event {
private:
    Game& game;
    Entity& entity;
    GameType::Direction moveDirection;

public:
    Move(Game& _game, Entity& _entity, GameType::Direction moveDirection);
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_MOVE_H
