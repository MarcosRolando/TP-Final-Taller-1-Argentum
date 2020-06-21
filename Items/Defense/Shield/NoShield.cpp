//
// Created by marcos on 18/6/20.
//

#include "NoShield.h"

using namespace GameType;

NoShield::NoShield(): Shield(Configuration::getInstance().configClothingData(NO_SHIELD)) {

}

bool NoShield::isDefault() const {
    return true;
}
