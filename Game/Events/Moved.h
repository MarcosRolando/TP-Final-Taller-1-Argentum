//
// Created by agustin on 29/6/20.
//

#ifndef ARGENTUM_MOVED_H
#define ARGENTUM_MOVED_H


#include "Event.h"
#include "../../Config/GameEnums.h"

#include <cstdint>

class Entity;
class ServerProtocol;

class Moved: public Event {
private:
    Entity& entity;
    GameType::Direction direction;
    int32_t displacement;

public:
    Moved(Entity& entity, GameType::Direction direction, int32_t displacement);
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_MOVED_H
