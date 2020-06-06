//
// Created by agustin on 6/6/20.
//

#include "Gold.h"


Gold::Gold(unsigned int ammount/* = 0*/) {
    this->ammount = ammount;
}

void Gold::use(int &player) {
    //nada
}

unsigned int Gold::getAmmount() {
    return ammount;
}
