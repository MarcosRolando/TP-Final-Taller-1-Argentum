//
// Created by agustin on 20/6/20.
//



#include "MonstersFactory.h"

#include "../Entities/Monster.h"
#include "../Config/Calculator.h"


////////////////////////////////////PRIVATE///////////////////////////

void MonstersFactory::_storeSpider(Game& game, Coordinate initialPosition, std::shared_ptr<Monster>& monster) {
    monster.reset(new Monster(game, initialPosition, GameType::SPIDER, GameType::SPIDER_ATTACK));
}

void MonstersFactory::_storeSkeleton(Game& game, Coordinate initialPosition, std::shared_ptr<Monster>& monster) {
    monster.reset(new Monster(game, initialPosition, GameType::SKELETON, GameType::SKELETON_ATTACK));
}

void MonstersFactory::_storeZombie(Game& game,Coordinate initialPosition, std::shared_ptr<Monster>& monster) {
        monster.reset(new Monster(game,initialPosition, GameType::ZOMBIE, GameType::ZOMBIE_ATTACK   ));
}

void MonstersFactory::_storeGoblin(Game& game, Coordinate initialPosition, std::shared_ptr<Monster>& monster) {
    monster.reset(new Monster(game, initialPosition, GameType::GOBLIN, GameType::GOBLIN_ATTACK));
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

void MonstersFactory::storeRandomMonster(Game& game, std::shared_ptr<Monster> &monster) {
    monsterCreators[existingMonsters[Calculator::getRandomInt(0, static_cast<int>(existingMonsters.size()) - 1)]]
                                    (game, {0, 0}, monster);
}


