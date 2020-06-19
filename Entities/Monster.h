//
// Created by agustin on 7/6/20.
//

#ifndef ARGENTUM_MONSTER_H
#define ARGENTUM_MONSTER_H


#include "Entity.h"
#include "../Game.h"


class Monster: public Entity {
private:
    const unsigned int timeBetweenActions;
    unsigned long timer;
    int currentLife;
    int maxLife;
    int damage;
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
    static unsigned int _getDistance(Coordinate a, Coordinate b);

    void _storeNearestPlayerPathCache();

    bool _tryToAttack();

    void _move();
public:

    Monster(Game& _game, const Map& map, int _life, unsigned int _rangeOfVision,
            unsigned int timeBetweenActions, Coordinate initialPosition);


    //Daña el monstruo, retorna la cantidad de danio recibido
    //Recibe level por un tema de herencia y logica del juego, esto igualmente
    //hace que el ataque sea extendible, podria aplicarse la logica del fair
    //play tambien a los monstruos
    AttackResult attacked(int damage, unsigned int attackerLevel) override;

    //Retorna true si el monstruo esta muerto, false si esta vivo
    bool isDead() const;

    void act();

    static std::shared_ptr<Item> dropLoot();
};


#endif //ARGENTUM_MONSTER_H
