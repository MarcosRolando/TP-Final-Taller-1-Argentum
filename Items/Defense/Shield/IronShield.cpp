//
// Created by agustin on 17/6/20.
//

#include "IronShield.h"

IronShield::IronShield(): Shield(Configuration::getInstance().configIronShieldStats(),
                                 "Escudo de hierro") {
}
