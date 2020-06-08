//
// Created by agustin on 7/6/20.
//

#ifndef ARGENTUM_GAME_H
#define ARGENTUM_GAME_H


#include "Map/Map.h"

class Game {
private:
    Map map;
public:
    unsigned int attackPosition(unsigned int damage, unsigned int level,
                            Coordinate coordinate);
};


#endif //ARGENTUM_GAME_H
