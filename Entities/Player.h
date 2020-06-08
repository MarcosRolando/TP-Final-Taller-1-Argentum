//
// Created by agustin on 8/6/20.
//

#ifndef ARGENTUM_PLAYER_H
#define ARGENTUM_PLAYER_H


#include "Inventory.h"

class Player {
private:
    Inventory inventory;
    unsigned int currentMana;
    unsigned int maxMana;
    unsigned int currentHealth;
    unsigned int maxHealth;
    Weapon equippedWeapon;
public:
    Player(unsigned int maxHealth, unsigned int maxMana);
};


#endif //ARGENTUM_PLAYER_H
