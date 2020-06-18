//
// Created by agustin on 6/6/20.
//

#include "Weapon.h"
#include "../../Config/Calculator.h"
#include <ctime>
#include <cstdlib>

//////////////////////////////////////PRIVATE//////////////////////

bool Weapon::_isTargetReachable(Coordinate attackPosition,
                               Coordinate attackedPosition) const {
    unsigned int distance = std::abs(attackPosition.iPosition - attackedPosition.iPosition) +
                            std::abs(attackPosition.jPosition - attackedPosition.jPosition);
    return (distance != 0) && (distance <= attackRange);
}



void Weapon::_initializeData(int _minDamage, int _maxDamage, unsigned int _manaConsumption,
                            unsigned int _range) {
    minDamage = _minDamage;
    maxDamage = _maxDamage;
    manaConsumption = _manaConsumption;
    attackRange = _range;
}



//////////////////////////////////////PUBLIC//////////////////////
Weapon::Weapon(const Config::WeaponData& stats): Item(stats.name, stats.price) {
    _initializeData(stats.minDmg, stats.maxDmg, stats.manaConsumption, stats.range);
}

//VER SI SE HACE QUE EN VEZ DE RETORNAR 0 TIRE UNA EXCEPCION
int Weapon::getDamage(Coordinate attackPosition, Coordinate attackedPosition) const{
    srand(clock());
    if (!_isTargetReachable(attackPosition, attackedPosition)) {
        return 0;
    }
   return Calculator::getRandomInt(minDamage, maxDamage);
}

EquipmentPlace Weapon::use(Player &player) {
    return EQUIPMENT_PLACE_WEAPON;
}

