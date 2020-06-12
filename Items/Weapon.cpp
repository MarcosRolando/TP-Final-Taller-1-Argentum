//
// Created by agustin on 6/6/20.
//

#include "Weapon.h"

#include <ctime>
#include <cstdlib>

//////////////////////////////////////PRIVATE//////////////////////

bool Weapon::_isTargetReachable(Coordinate attackPosition,
                               Coordinate attackedPosition) const {
    unsigned int distance = std::abs(attackPosition.iPosition - attackedPosition.iPosition) +
                            std::abs(attackPosition.jPosition - attackedPosition.jPosition);
    return (distance != 0) && (distance <= attackRange);
}



void Weapon::_initializeData(unsigned int _minDamage, unsigned int _maxDamage) {
    this->minDamage = _minDamage;
    this->maxDamage = _maxDamage;
}



//////////////////////////////////////PUBLIC//////////////////////

//VER SI ESTO SE SACA DE ACA
Weapon::Weapon(): Item("Puños"){
    _initializeData(1, 1);
}


Weapon::Weapon(unsigned int minDamage, unsigned int maxDamage, std::string& _name): Item(_name) {
    _initializeData(minDamage, maxDamage);
}

Weapon::Weapon(unsigned int minDamage, unsigned int maxDamage, std::string &&_name): Item(std::move(_name)){
    _initializeData(minDamage, maxDamage);
}


//VER SI SE HACE QUE EN VEZ DE RETORNAR 0 TIRE UNA EXCEPCION
unsigned int Weapon::getDamage(Coordinate attackPosition, Coordinate attackedPosition) const{
    srand(clock());
    if (!_isTargetReachable(attackPosition, attackedPosition)) {
        return 0;
    }
    //Devuelve un numero aleatorio entre minDamage y maxDamage (incluidos)
    return (rand() % (maxDamage - minDamage + 1)) + minDamage;
}

EquipmentPlace Weapon::use(Player &player) {
    return EQUIPMENT_PLACE_WEAPON;
}




