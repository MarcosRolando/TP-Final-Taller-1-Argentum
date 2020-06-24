//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_ATTACK_H
#define ARGENTUM_ATTACK_H


#include "Event.h"
#include "../../Map/Coordinate.h"

class Entity;

class Attack : public Event {
private:
    Entity& entity;
    Coordinate target{};

public:
    Attack(Entity& _entity, Coordinate _target);
    void operator()();
};


#endif //ARGENTUM_ATTACK_H
