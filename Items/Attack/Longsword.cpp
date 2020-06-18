//
// Created by agustin on 18/6/20.
//

#include "Longsword.h"

using namespace Config;

Longsword::Longsword(): Weapon(Configuration::getInstance().configWeaponData(LONGSWORD)) {

}
