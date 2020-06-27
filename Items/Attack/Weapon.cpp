//
// Created by agustin on 6/6/20.
//

#include "Weapon.h"
#include "../../Config/Calculator.h"
#include "../../Map/Coordinate.h"
#include "../../Config/Configuration.h"
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
Weapon::Weapon(GameType::Weapon weapon): Item(GameType::ITEM_TYPE_WEAPON,
                                              Configuration::getInstance().configWeaponData(weapon).name/*,
                                              Configuration::getInstance().configWeaponData(weapon).price*/) {
    Config::WeaponData stats = Configuration::getInstance().configWeaponData(weapon);
    id = static_cast<unsigned int>(weapon);
    _initializeData(stats.minDmg, stats.maxDmg, stats.manaConsumption, stats.range);
}

int Weapon::getDamage(Coordinate attackPosition, Coordinate attackedPosition,
                    unsigned int& currentMana) const {
    if (!_isTargetReachable(attackPosition, attackedPosition) ||
        manaConsumption > currentMana ) {
        return 0;
    }
    currentMana -= manaConsumption;
    return Calculator::getRandomInt(minDamage, maxDamage);
}

EquipmentPlace Weapon::use(Player &player) {
    return EQUIPMENT_PLACE_WEAPON;
}

Weapon::~Weapon() = default;

bool Weapon::isDefault() {
    return (static_cast<GameType::Weapon>(id) == GameType::Weapon::FIST);
}

