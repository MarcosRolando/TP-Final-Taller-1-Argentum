//
// Created by marcos on 18/6/20.
//

#include "CommonClothing.h"

using namespace GameType;

CommonClothing::CommonClothing() : Chest(Configuration::getInstance().configClothingData(COMMON_CLOTHING)){

}

bool CommonClothing::isDefault() const {
    return true;
}
