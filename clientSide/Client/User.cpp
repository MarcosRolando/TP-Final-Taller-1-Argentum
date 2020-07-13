#include "User.h"
#include <iostream>
#include <string>

std::string User::getInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void User::showMessage(const char* message) {
    std::cout << message << std::endl;
}
