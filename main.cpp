//
// Created by marcos on 6/3/20.
//

#include "Game/Argentum.h"
#include "TPException.h"
#include <iostream>

int main() {
    try {
        Argentum game;
        game.execute();
    } catch (TPException& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Algo rompio bro" << std::endl;
    }
    return 0;
}
