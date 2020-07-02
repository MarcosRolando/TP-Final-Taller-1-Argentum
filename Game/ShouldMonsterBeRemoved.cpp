//
// Created by agustin on 21/6/20.
//

#include "ShouldMonsterBeRemoved.h"

#include "../Entities/Monster.h"

ShouldMonsterBeRemoved::ShouldMonsterBeRemoved(std::list <Coordinate> &monstersToRemove):
                                               monstersToRemove(monstersToRemove) {

}

bool ShouldMonsterBeRemoved::operator()(const Monster* monster) {
    if (monster->isDead()) {
        monstersToRemove.push_back(monster->getPosition());
        return true;
    }
    return false;
}
