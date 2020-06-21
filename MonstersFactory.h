//
// Created by agustin on 20/6/20.
//

#ifndef ARGENTUM_MONSTERSFACTORY_H
#define ARGENTUM_MONSTERSFACTORY_H

#include <unordered_map>
#include <vector>
#include <memory>
#include "Config/GameEnums.h"
#include "Map/Coordinate.h"

class Monster;
class Game;
class Map;

typedef void (*monsterCreator)(Game& game, Map& map, Coordinate initialPosition,
                               std::shared_ptr<Monster>& monster);

class MonstersFactory {
private:
    std::unordered_map<GameType::Monster, monsterCreator> monsterCreators;
    std::vector<GameType::Monster> existingMonsters;
private:
    static void _storeSpider(Game& game, Map& map, Coordinate initialPosition,
                             std::shared_ptr<Monster>& monster);
    static void _storeSkeleton(Game& game, Map& map, Coordinate initialPosition,
                               std::shared_ptr<Monster>& monster);
    static void _storeZombie(Game& game, Map& map, Coordinate initialPosition,
                             std::shared_ptr<Monster>& monster);
    static void _storeGoblin(Game& game, Map& map, Coordinate initialPosition,
                             std::shared_ptr<Monster>& monster);

public:
    MonstersFactory();
    void storeRandomMonster(Game& game, Map& map, std::shared_ptr<Monster>& monster, Coordinate initialPosition);
};


#endif //ARGENTUM_MONSTERSFACTORY_H
