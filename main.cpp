#include <iostream>
#include "FileReader.h"
#include "Configuration.h"

int main() {
    std::cout <<"mindef "<< Configuration::getInstance()
    .configLeatherArmorStats().minDefense << std::endl;
    std::cout <<"maxdef "<< Configuration::getInstance()
            .configLeatherArmorStats().maxDefense << std::endl;

    return 0;
}
