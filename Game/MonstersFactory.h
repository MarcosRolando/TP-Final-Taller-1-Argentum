//
// Created by agustin on 20/6/20.
//

#ifndef ARGENTUM_MONSTERSFACTORY_H
#define ARGENTUM_MONSTERSFACTORY_H

#include <unordered_map>
#include <vector>
#include <memory>
#include "../Config/GameEnums.h"
#include "../Map/Coordinate.h"

class GameTests;
class Monster;
class Game;
class Map;

typedef void (*monsterCreator)(Game& game, Coordinate initialPosition,
                               std::shared_ptr<Monster>& monster);

class MonstersFactory {
private:
    std::unordered_map<GameType::Entity, monsterCreator> monsterCreators;
    std::vector<GameType::Entity> existingMonsters;

    friend GameTests;

private:
    static void _storeSpider(Game& game, Coordinate initialPosition,
                             std::shared_ptr<Monster>& monster);
    static void _storeSkeleton(Game& game, Coordinate initialPosition,
                               std::shared_ptr<Monster>& monster);
    static void _storeZombie(Game& game, Coordinate initialPosition,
                             std::shared_ptr<Monster>& monster);
    static void _storeGoblin(Game& game, Coordinate initialPosition,
                             std::shared_ptr<Monster>& monster);

public:
    MonstersFactory();

    //Guarda en monster un monstruo aleatorio, la coordenada inicial es el {0, 0}
    void storeRandomMonster(Game& game, std::shared_ptr<Monster>& monster);
};


#endif //ARGENTUM_MONSTERSFACTORY_H
