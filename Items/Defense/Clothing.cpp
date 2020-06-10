//
// Created by agustin on 9/6/20.
//

#include "Clothing.h"

Clothing::Clothing(unsigned int _minDefense, unsigned int _maxDefense) {
    minDefense = _minDefense;
    maxDefense = _maxDefense;
}

unsigned int Clothing::getDefense() {
    return (rand() % (maxDefense - minDefense + 1)) + minDefense;
}
