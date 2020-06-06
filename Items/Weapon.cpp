//
// Created by agustin on 6/6/20.
//

#include "Weapon.h"

#include <ctime>
#include <cstdlib>


Weapon::Weapon(unsigned int minDamage, unsigned int maxDamage) {
    this->minDamage = minDamage;
    this->maxDamage = maxDamage;
}


//VER QUE HACER CON EL DESTRUCTOR PORQUE SE VA A USAR EL DEFAULT


unsigned int Weapon::getDamage() {
    srand(clock());
    //Devuelve un numero aleatorio entre minDamage y maxDamage (incluidos)
    return (rand() % (maxDamage - minDamage + 1)) + minDamage;
}