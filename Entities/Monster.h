//
// Created by agustin on 7/6/20.
//

#ifndef ARGENTUM_MONSTER_H
#define ARGENTUM_MONSTER_H


#include "Entity.h"
#include <memory>
#include "MonsterStats.h"
#include "../Config/GameEnums.h"

class Game;
class Map;
class Item;

class Monster: public Entity {
private:
    const unsigned int timeBetweenActions;
    unsigned long timer;
    MonsterStats stats;
    GameType::Monster type;

    //Guarda parte del camino para no llamar al pathfinding cada vez que se
    //quiera mover
    std::list<Coordinate> pathCache;

    //Guarda el mapa para ver sus alrededores, el juego lo guarda para poder
    //modificarlo
    const Map& map;
    Game& game;
private:
    static unsigned int _getDistance(Coordinate a, Coordinate b);

    void _storeNearestPlayerPathCache();

    bool _tryToAttack();

    void _move();

    Direction _getMoveDirection();
public:

    Monster(Game& _game, const Map& map, Coordinate initialPositionunsigned,
            GameType::Monster _type);


    //Daña el monstruo, retorna la cantidad de danio recibido
    //Recibe level por un tema de herencia y logica del juego, esto igualmente
    //hace que el ataque sea extendible, podria aplicarse la logica del fair
    //play tambien a los monstruos
    AttackResult attacked(int damage, unsigned int attackerLevel) override;

    void act();

    bool isDead();
};


#endif //ARGENTUM_MONSTER_H
