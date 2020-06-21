//
// Created by agustin on 20/6/20.
//

#ifndef ARGENTUM_MONSTERSFACTORY_H
#define ARGENTUM_MONSTERSFACTORY_H

#include <unordered_map>
#include <list>
#include <memory>
#include "Config/GameEnums.h"

class Monster;

typedef void (*monsterCreator)(std::unique_ptr<Monster>& monster);

class MonstersFactory {
private:
    std::unordered_map<GameType::Monster, monsterCreator> monsterCreators;
    std::list<GameType::Monster> existingMonsters;
private:
    static void _storeSpider(std::unique_ptr<Monster>& monster);
    static void _storeSkeleton(std::unique_ptr<Monster>& monster);
    static void _storeZombie(std::unique_ptr<Monster>& monster);
    static void _storeGoblin(std::unique_ptr<Monster>& monster);

public:
    MonstersFactory();
    void storeRandomMonster(std::unique_ptr<Monster>& monster);
};


#endif //ARGENTUM_MONSTERSFACTORY_H
