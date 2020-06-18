//
// Created by agustin on 18/6/20.
//

#include "SimpleBow.h"

using namespace Config;

SimpleBow::SimpleBow(): Weapon(Configuration::getInstance().configWeaponData(SIMPLE_BOW)) {

}
