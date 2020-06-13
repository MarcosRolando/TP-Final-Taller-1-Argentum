//
// Created by agustin on 7/6/20.
//

#ifndef ARGENTUM_MONSTER_H
#define ARGENTUM_MONSTER_H


#include "Entity.h"
#include "../Game.h"

class Monster: public Entity{
private:
    const unsigned int timeBetweenActions;
    unsigned long timer;
    int health;
    unsigned int damage;
    unsigned int rangeOfVision;
    unsigned int level;

    //Guarda parte del camino para no llamar al pathfinding cada vez que se
    //quiera mover
    std::list<Coordinate> pathCache;

    //Guarda el mapa para ver sus alrededores, el juego lo guarda para poder
    //modificarlo
    const Map& map;
    Game& game;
private:
    unsigned int _getDistance(Coordinate a, Coordinate b);

    void _storeNearestPlayerPathCache();

    bool _tryToAttack();

    void _move();
public:

    Monster(Game& _game, const Map& map, unsigned int _health, unsigned int _rangeOfVision,
            unsigned int timeBetweenActions, Coordinate initialPosition);


    //Daña el monstruo, retorna la cantidad de danio recibido
    //Recibe level por un tema de herencia y logica del juego, esto igualmente
    //hace que el ataque sea extendible, podria aplicarse la logica del fair
    //play tambien a los monstruos
    unsigned int attacked(unsigned int damage, unsigned int level) override;

    //Retorna true si el monstruo esta muerto, false si esta vivo
    bool isDead();

    void act();
};


#endif //ARGENTUM_MONSTER_H
