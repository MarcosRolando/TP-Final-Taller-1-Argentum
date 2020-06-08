//
// Created by agustin on 8/6/20.
//

#ifndef ARGENTUM_PLAYER_H
#define ARGENTUM_PLAYER_H


#include "Inventory.h"
#include "Entity.h"

enum Direction{
    DIRECTION_UP, DIRECTION_DOWN, DIRECTION_LEFT, DIRECTION_RIGHT
};


class Player: public Entity {
private:
    Inventory inventory;
    unsigned int currentMana;
    //unsigned int maxMana;
    unsigned int currentHealth;
    //unsigned int maxHealth;
    unsigned int level;
    unsigned int experience;
    Weapon equippedWeapon;
public:
    Player(unsigned int maxHealth, unsigned int maxMana);

    //Modifica la posicion almacenada por el jugador, para que luego sea actualizada
    //por el juego
    void move(Direction direction);


    //IMPLEMENTAR
    void attack(Coordinate target);
};


#endif //ARGENTUM_PLAYER_H
