//
// Created by agustin on 21/6/20.
//

#include "ShouldMonsterBeRemoved.h"

#include "../Entities/Monster.h"

ShouldMonsterBeRemoved::ShouldMonsterBeRemoved(std::list<std::pair<Coordinate, const std::string*>> &monstersToRemove):
                                               monstersToRemove(monstersToRemove) {

}

bool ShouldMonsterBeRemoved::operator()(const Monster* monster) {
    if (monster->isDead()) {
        std::pair<Coordinate, const std::string*> aux(monster->getPosition(), &(monster->getNickname()));
        monstersToRemove.push_back(std::move(aux));
        return true;
    }
    return false;
}
