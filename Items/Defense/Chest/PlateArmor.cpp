//
// Created by agustin on 17/6/20.
//

#include "PlateArmor.h"

using namespace Config;

PlateArmor::PlateArmor(): Chest(Configuration::getInstance().configClothingStats(PLATE_ARMOR),
                               "Armadura de placas") {

}
