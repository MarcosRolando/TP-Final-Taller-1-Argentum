//
// Created by agustin on 9/6/20.
//

#include "Clothing.h"

#include <string>

/*
Clothing::Clothing(unsigned int _minDefense, unsigned int _maxDefense, std::string name):
                   Item(name) {
    minDefense = _minDefense;
    maxDefense = _maxDefense;
}
*/

Clothing::Clothing(Config::ClothingStats stats, const std::string& name): Item(name) {
    minDefense = stats.minDefense;
    maxDefense = stats.maxDefense;
}


unsigned int Clothing::getDefense() {
    return (rand() % (maxDefense - minDefense + 1)) + minDefense;
}

