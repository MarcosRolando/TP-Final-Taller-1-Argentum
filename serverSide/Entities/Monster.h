//
// Created by agustin on 7/6/20.
//

#ifndef ARGENTUM_MONSTER_H
#define ARGENTUM_MONSTER_H


#include "Entity.h"
#include <memory>
#include "MonsterStats.h"
#include "../../libs/GameEnums.h"

class Game;
class Map;
class Item;
class EntityTests;

class Monster: public Entity {
private:
    const unsigned int timeBetweenActions;
    double elapsedTime;
    int inactiveCycles;
    MonsterStats stats;
    GameType::Weapon monsterWeapon;

    /*Guarda parte del camino para no llamar al pathfinding cada vez que se
    quiera mover*/
    std::list<Coordinate> pathCache;

    /*Guarda el mapa para ver sus alrededores, el juego lo guarda para poder
    modificarlo*/
    const Map& map;
    Game& game;

    friend EntityTests;

private:
    static unsigned int _getDistance(Coordinate a, Coordinate b);

    void _storeNearestPlayerPathCache();

    bool _tryToAttack();

    void _move();

public:
    Monster(Game& _game, Coordinate initialPositionunsigned,
            GameType::Entity _type, GameType::Weapon _weapon);


    /*Daña el monstruo, retorna la cantidad de danio recibido
    Recibe level por un tema de herencia y logica del juego, esto igualmente
    hace que el ataque sea extendible, podria aplicarse la logica del fair
    play tambien a los monstruos. El isAPlayer no lo usa pero hacia falta
    para el polimorfismo de Player*/
    AttackResult attacked(int damage, unsigned int attackerLevel, bool isAPlayer) override;

    /*Actualiza al monstruo acorde a su estado (por ejemplo si esta moviendose
     * actualiza la interpolacion, o si tiene a un playera la vista lo
     * ataca*/
    void update(double timeStep);

    /*Indica si el monstruo esta muerto, retorna true si lo esta, sino retorna false*/
    bool isDead() const;

    /*Ataca una posicion (lo hace cuando tiene un player a la vista*/
    int32_t attack(Coordinate attackedPosition) override;

    int32_t getLevel() const override;
};


#endif //ARGENTUM_MONSTER_H
