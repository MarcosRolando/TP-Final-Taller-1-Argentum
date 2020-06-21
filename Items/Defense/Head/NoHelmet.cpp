//
// Created by marcos on 18/6/20.
//

#include "NoHelmet.h"

using namespace GameType;

NoHelmet::NoHelmet() : Head(Configuration::getInstance().configClothingData(NO_HELMET)){

}

bool NoHelmet::isDefault() const {
    return true;
}
