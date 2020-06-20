//
// Created by agustin on 17/6/20.
//

#include "IronHelmet.h"

#include "../../../Config/Configuration.h"

using namespace GameType;

IronHelmet::IronHelmet(): Head(Configuration::getInstance().configClothingData(IRON_HELMET)) {

}
