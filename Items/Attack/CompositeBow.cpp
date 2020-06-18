//
// Created by agustin on 17/6/20.
//

#include "CompositeBow.h"

using namespace Config;

CompositeBow::CompositeBow(): Weapon(Configuration::getInstance().configWeaponData(COMPOSITE_BOW)) {

}
