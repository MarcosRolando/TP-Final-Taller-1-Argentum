//
// Created by agustin on 17/6/20.
//

#include "IronHelmet.h"

#include "../../../Config/Configuration.h"

IronHelmet::IronHelmet(): Head(Configuration::getInstance().configClothingData(Config::IRON_HELMET)) {

}
