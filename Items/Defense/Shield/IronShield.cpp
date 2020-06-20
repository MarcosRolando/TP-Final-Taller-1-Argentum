//
// Created by agustin on 17/6/20.
//

#include "IronShield.h"

using namespace GameType;

IronShield::IronShield(): Shield(Configuration::getInstance().configClothingData(IRON_SHIELD)) {
}
