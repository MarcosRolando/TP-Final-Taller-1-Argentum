//
// Created by agustin on 17/6/20.
//

#include "LeatherArmor.h"

using namespace Config;

LeatherArmor::LeatherArmor(): Chest(Configuration::getInstance().configClothingStats(LEATHER_ARMOR)) {

}
