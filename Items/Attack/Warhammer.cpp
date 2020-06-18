//
// Created by agustin on 18/6/20.
//

#include "Warhammer.h"

using namespace Config;

Warhammer::Warhammer(): Weapon(Configuration::getInstance().configWeaponStats(WARHAMMER)) {

}
