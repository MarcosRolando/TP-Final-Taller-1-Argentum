//
// Created by agustin on 9/6/20.
//

#include "Clothing.h"
#include "../../Config/Calculator.h"

Clothing::Clothing(GameType::Clothing clothing): Item(GameType::ITEM_TYPE_CLOTHING,
                Configuration::getInstance().configClothingData(clothing).name) {
    Config::ClothingData stats = Configuration::getInstance().configClothingData(clothing);
    id = static_cast<unsigned int>(clothing);
    minDefense = stats.minDefense;
    maxDefense = stats.maxDefense;
}

unsigned int Clothing::getDefense() const {
    return Calculator::getRandomInt(static_cast<int>(minDefense),
                                    static_cast<int>(maxDefense));
}


