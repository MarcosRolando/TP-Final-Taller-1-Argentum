//
// Created by agustin on 20/6/20.
//



#include "MonstersFactory.h"

#include "Entities/Monster.h"


////////////////////////////////////PRIVATE///////////////////////////

void MonstersFactory::_storeSpider(std::unique_ptr<Monster> &monster) {
    monster.reset(new Monster(GameType::SPIDER));
}

void MonstersFactory::_storeSkeleton(std::unique_ptr<Monster> &monster) {
    monster.reset(new Monster(GameType::SKELETON));
}

void MonstersFactory::_storeZombie(std::unique_ptr<Monster> &monster) {
    monster.reset(new Monster(GameType::ZOMBIE));
}

void MonstersFactory::_storeGoblin(std::unique_ptr<Monster> &monster) {
    monster.reset(new Monster(GameType::GOBLIN));
}

////////////////////////////////////PUBLIC///////////////////////////

MonstersFactory::MonstersFactory() {
    monsterCreators[GameType::SPIDER] = _storeSpider;
    monsterCreators[GameType::SKELETON] = _storeSkeleton;
    monsterCreators[GameType::ZOMBIE] = _storeZombie;
    monsterCreators[GameType::GOBLIN] = _storeGoblin;

    for (const auto & creator: monsterCreators) {
        existingMonsters.push_back(creator.first);
    }
}

void MonstersFactory::storeRandomMonster(std::unique_ptr<Monster> &monster) {
    Calculator::getRandom
}


