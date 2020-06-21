//
// Created by agustin on 9/6/20.
//

#include "Clothing.h"
#include "../../Config/Calculator.h"

/*
Clothing::Clothing(unsigned int _minDefense, unsigned int _maxDefense, std::string name):
                   Item(name) {
    minDefense = _minDefense;
    maxDefense = _maxDefense;
}
*/

/*
Clothing::Clothing(const Config::ClothingData& stats): Item(stats.name, stats.price) {
    minDefense = stats.minDefense;
    maxDefense = stats.maxDefense;
}
*/

Clothing::Clothing(GameType::Clothing clothing): Item(Configuration::getInstance().configClothingData(clothing).name,
                                                      Configuration::getInstance().configClothingData(clothing).price) {
    Config::ClothingData stats = Configuration::getInstance().configClothingData(clothing);
    minDefense = stats.minDefense;
    maxDefense = stats.maxDefense;
}


unsigned int Clothing::getDefense() const {
    return Calculator::getRandomInt(minDefense, maxDefense);
}

bool Clothing::isDefault() const {
    return false;
}

