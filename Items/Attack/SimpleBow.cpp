//
// Created by agustin on 18/6/20.
//

#include "SimpleBow.h"

using namespace Config;

SimpleBow::SimpleBow(): Weapon(Configuration::getInstance().configWeaponStats(SIMPLE_BOW)) {

}
