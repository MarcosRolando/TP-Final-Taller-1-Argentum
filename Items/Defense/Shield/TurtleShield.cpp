//
// Created by agustin on 17/6/20.
//

#include "TurtleShield.h"

using namespace GameType;

TurtleShield::TurtleShield(): Shield(Configuration::getInstance().configClothingData(TURTLE_SHIELD)) {
}
