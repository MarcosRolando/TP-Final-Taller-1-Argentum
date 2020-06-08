//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_ENTITY_H
#define ARGENTUM_ENTITY_H


#include "../Map/Coordinate.h"

class Entity {
protected:
    Coordinate currentPosition;

public:
    explicit Entity(Coordinate initialPosition);
    virtual unsigned int attacked(unsigned int damage, unsigned int level) = 0;
};


#endif //ARGENTUM_ENTITY_H
