//
// Created by agustin on 9/6/20.
//

#include "Clothing.h"
#include "../../Config/Calculator.h"


Clothing::Clothing(GameType::Clothing clothing): Item(ITEM_TYPE_CLOTHING,
                                                    Configuration::getInstance().configClothingData(clothing).name,
                                                      Configuration::getInstance().configClothingData(clothing).price) {
    Config::ClothingData stats = Configuration::getInstance().configClothingData(clothing);
    minDefense = stats.minDefense;
    maxDefense = stats.maxDefense;
}


unsigned int Clothing::getDefense() const {
    return Calculator::getRandomInt(static_cast<int>(minDefense),
                                    static_cast<int>(maxDefense));
}

bool Clothing::isDefault() const {
    return false;
}

