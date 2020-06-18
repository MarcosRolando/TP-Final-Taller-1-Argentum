//
// Created by agustin on 17/6/20.
//

#include "IronShield.h"

using namespace Config;

IronShield::IronShield(): Shield(Configuration::getInstance().configClothingStats(IRON_SHIELD),
                                 "Escudo de hierro") {
}
