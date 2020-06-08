//
// Created by agustin on 7/6/20.
//

#ifndef ARGENTUM_MONSTER_H
#define ARGENTUM_MONSTER_H


#include "Entity.h"

class Monster: public Entity{
private:
    int health;
    unsigned int damage;
    unsigned int rangeOfVision;
    Game& game;
public:
    //Retorna el daño que el monstruo intenta realizar
    unsigned int attack();

    //Daña el monstruo
    unsigned int attacked(unsigned int damage);

    //Retorna true si el monstruo esta muerto, false si esta vivo
    bool isDead();
};


#endif //ARGENTUM_MONSTER_H
