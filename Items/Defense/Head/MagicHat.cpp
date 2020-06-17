//
// Created by agustin on 17/6/20.
//

#include "MagicHat.h"

#include "../../../Config/Configuration.h"

MagicHat::MagicHat(): Head(Configuration::getInstance().configMagicHatStats(), "Sombrero mágico") {

}
