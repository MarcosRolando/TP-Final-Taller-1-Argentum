#include <iostream>
#include "FileReader.h"
#include "Configuration.h"

int main() {
    Configuration::getInstance().getClericModifiers();

    return 0;
}
