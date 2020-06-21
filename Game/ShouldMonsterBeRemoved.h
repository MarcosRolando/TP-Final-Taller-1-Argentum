//
// Created by agustin on 21/6/20.
//

#ifndef ARGENTUM_SHOULDMONSTERBEREMOVED_H
#define ARGENTUM_SHOULDMONSTERBEREMOVED_H

#include <list>
#include <memory>
#include "../Map/Coordinate.h"

class Monster;

class ShouldMonsterBeRemoved {
private:
    std::list<Coordinate>& monstersToRemove;
public:
    explicit ShouldMonsterBeRemoved(std::list<Coordinate>& monstersToRemove);

    bool operator()(const std::shared_ptr<Monster>& monster);
};






#endif //ARGENTUM_SHOULDMONSTERBEREMOVED_H
