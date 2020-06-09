//
// Created by agustin on 7/6/20.
//

#ifndef ARGENTUM_MONSTER_H
#define ARGENTUM_MONSTER_H


#include "Entity.h"
#include "../Game.h"

class Monster: public Entity{
private:
    int health;
    unsigned int damage;
    unsigned int rangeOfVision;
    //Guarda el mapa para ver sus alrededores, el juego lo guarda para poder
    //modificarlo
    const Map& map;
    Game& game;
public:
    Monster(Game& _game, const Map& map, unsigned int _health, unsigned int _rangeOfVision);

    //Retorna el daño que el monstruo intenta realizar
    //VER SI ESTE RETORNO ES NECESARIO
    unsigned int attack();

    void move();

    bool isMonsterTarget() override;

    //Daña el monstruo, retorna la cantidad de danio recibido
    //Recibe level por un tema de herencia y logica del juego, esto igualmente
    //hace que el ataque sea extendible, podria aplicarse la logica del fair
    //play tambien a los monstruos
    unsigned int attacked(unsigned int damage, unsigned int level);

    //Retorna true si el monstruo esta muerto, false si esta vivo
    bool isDead();
};


#endif //ARGENTUM_MONSTER_H
