//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_WEAPON_H
#define ARGENTUM_WEAPON_H


#include "Item.h"

class Weapon: public Item {
private:
    unsigned int minDamage;
    unsigned int maxDamage;

public:


    Weapon(unsigned int minDamage, unsigned int maxDamage);

    //Devuelve el danio que haria el arma por sí sola, es un numero aleatorio
    //entre el danio minimo y el maximo
    unsigned int getDamage() const;


};


#endif //ARGENTUM_WEAPON_H
