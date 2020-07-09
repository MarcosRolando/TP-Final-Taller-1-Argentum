//
// Created by marcos on 6/3/20.
//

#include "Server/ArgentumServerSide.h"
#include "TPException.h"
#include <iostream>

int main(int argc, char** argv) {
    try {
        ArgentumServerSide::run(argc, argv);
    } catch (TPException& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Algo rompio bro" << std::endl;
    }
    return 0;
}
