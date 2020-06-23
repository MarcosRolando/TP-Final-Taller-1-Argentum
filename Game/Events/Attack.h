//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_ATTACK_H
#define ARGENTUM_ATTACK_H


#include "Event.h"
#include "../../Map/Coordinate.h"

class Attack: public Event {
public:
    explicit Attack(Coordinate coordinate);
};


#endif //ARGENTUM_ATTACK_H
