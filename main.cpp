#include <iostream>
#include "FileReader.h"
#include "Configuration.h"

int main() {
    std::cout <<"crit"<< Configuration::getInstance()
    .configCriticalAttackChance();
    std::cout <<"crit"<< Configuration::getInstance().configDodgeChance();
    std::cout <<"crit"<< Configuration::getInstance().configInventorySize();
    std::cout <<"crit"<< Configuration::getInstance().configPlayerVisionRange();

    return 0;
}
