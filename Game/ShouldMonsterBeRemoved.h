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
    std::list<std::pair<Coordinate, const std::string*>>& monstersToRemove;
public:
    explicit ShouldMonsterBeRemoved(std::list<std::pair<Coordinate, const std::string*>>& monstersToRemove);

    bool operator()(const Monster* monster);
};






#endif //ARGENTUM_SHOULDMONSTERBEREMOVED_H
