//
// Created by agustin on 20/6/20.
//



#include "MonstersFactory.h"

#include "Entities/Monster.h"
#include "Config/Calculator.h"


////////////////////////////////////PRIVATE///////////////////////////

void MonstersFactory::_storeSpider(Game& game, Map& map, Coordinate initialPosition, std::shared_ptr<Monster>& monster) {
    monster.reset(new Monster(game, map, initialPosition, GameType::SPIDER));
}

void MonstersFactory::_storeSkeleton(Game& game, Map& map, Coordinate initialPosition, std::shared_ptr<Monster>& monster) {
    monster.reset(new Monster(game, map, initialPosition, GameType::SKELETON));
}

void MonstersFactory::_storeZombie(Game& game, Map& map, Coordinate initialPosition, std::shared_ptr<Monster>& monster) {
    monster.reset(new Monster(game, map, initialPosition, GameType::ZOMBIE));
}

void MonstersFactory::_storeGoblin(Game& game, Map& map, Coordinate initialPosition, std::shared_ptr<Monster>& monster) {
    monster.reset(new Monster(game, map, initialPosition, GameType::GOBLIN));
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

void MonstersFactory::storeRandomMonster(Game& game, Map& map, std::shared_ptr<Monster> &monster, Coordinate initialPosition) {
    monsterCreators[existingMonsters.Calculator::getRandomInt(0, existingMonsters.size() - 1)]](monster, initialPosition);
    //todo la lista no tiene operador [] asi que no podemos acceder asi a un elemento cualquiera
}


