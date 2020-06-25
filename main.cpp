//
// Created by marcos on 6/3/20.
//

#include "Server/ArgentumServer.h"
#include "TPException.h"
#include <iostream>

int main() {
    try {
        ArgentumServer game("8081");
        game.connect();
    } catch (TPException& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Algo rompio bro" << std::endl;
    }
    return 0;
}
