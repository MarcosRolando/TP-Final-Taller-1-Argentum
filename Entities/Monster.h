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
    double elapsedTime;
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
    //play tambien a los monstruos. El isAPlayer no lo usa pero hacia falta
    //para el polimorfismo de Player
    AttackResult attacked(int damage, unsigned int attackerLevel, bool isAPlayer) override;

    void update(double timeStep) override;

    //Indica si el monstruo esta muerto, retorna true si lo esta, sino retorna false
    bool isDead() const;
};


#endif //ARGENTUM_MONSTER_H
