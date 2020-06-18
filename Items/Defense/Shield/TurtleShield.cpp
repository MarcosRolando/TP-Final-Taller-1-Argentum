//
// Created by agustin on 17/6/20.
//

#include "TurtleShield.h"

using namespace Config;

TurtleShield::TurtleShield(): Shield(Configuration::getInstance().configClothingData(Config::TURTLE_SHIELD)) {
}
