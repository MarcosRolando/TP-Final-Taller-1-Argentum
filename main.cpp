#include <iostream>
#include "FileReader.h"
#include "Configuration.h"

int main() {
    std::cout <<"skeleton dmg"<< Configuration::getInstance()
    .configSkeletonStats().damage;
    std::cout <<"zombie dmg"<< Configuration::getInstance()
    .configZombieStats().damage;
    std::cout <<"spider dmg"<< Configuration::getInstance()
    .configSpiderStats().damage;
    std::cout <<"goblin dmg"<< Configuration::getInstance()
    .configGoblinStats().damage;

    return 0;
}
