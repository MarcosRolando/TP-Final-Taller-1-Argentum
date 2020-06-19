//
// Created by marcos on 18/6/20.
//

#include "Fist.h"

using namespace Config;

Fist::Fist() : Weapon(Configuration::getInstance().configWeaponData(FIST)) {

}

bool Fist::isDefault() {
    return true;
}
