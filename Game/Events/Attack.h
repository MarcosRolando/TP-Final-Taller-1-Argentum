//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_ATTACK_H
#define ARGENTUM_ATTACK_H


#include "Event.h"
#include "../../Map/Coordinate.h"

class Player;
class Monster;

class Attack: public Event {
public:
    explicit Attack(Player& entity, Coordinate target);
    explicit Attack(Monster& entity, Coordinate target);
};


#endif //ARGENTUM_ATTACK_H
