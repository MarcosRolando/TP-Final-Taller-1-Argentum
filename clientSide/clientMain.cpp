#include "Client/ArgentumClientSide.h"
#include "../libs/TPException.h"
#include <iostream>

int main(int argc, char** argv) {
    try {
        ArgentumClientSide::run(argc);
    } catch (TPException& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Uknown error in Client!" << std::endl;
    }
}
