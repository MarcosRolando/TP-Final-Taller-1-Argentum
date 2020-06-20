//
// Created by marcos on 18/6/20.
//

#include "Fist.h"

using namespace GameType;

Fist::Fist() : Weapon(Configuration::getInstance().configWeaponData(FIST)) {

}

bool Fist::isDefault() {
    return true;
}
