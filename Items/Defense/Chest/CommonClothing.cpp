//
// Created by marcos on 18/6/20.
//

#include "CommonClothing.h"

using namespace Config;

CommonClothing::CommonClothing() : Chest(Configuration::getInstance().configClothingData(COMMON_CLOTHING)){

}

bool CommonClothing::isDefault() {
    return true;
}
