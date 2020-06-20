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
    AttackResult attackPosition(int damage, unsigned int level,
                            Coordinate coordinate);
    void dropItems(std::list<std::shared_ptr<Item>>&& items, Coordinate position);
    void dropItems(std::shared_ptr<Item>&& item, Coordinate position);
};


#endif //ARGENTUM_GAME_H
