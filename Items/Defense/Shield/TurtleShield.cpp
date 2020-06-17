//
// Created by agustin on 17/6/20.
//

#include "TurtleShield.h"

#include "../../../Config/Configuration.h"

TurtleShield::TurtleShield(): Shield(Configuration::getInstance().configTurtleShieldStats(),
                                     "Escudo de tortuga") {
}
