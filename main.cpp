#include <iostream>
#include "FileReader.h"
#include "Configuration.h"

int main() {
    std::cout <<"crit"<< Configuration::getInstance()
    .configCriticalAttackChance();
    std::cout <<"dodge"<< Configuration::getInstance().configDodgeChance();
    std::cout <<"range"<< Configuration::getInstance()
    .configPlayerVisionRange();

    return 0;
}
