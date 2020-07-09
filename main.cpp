//
// Created by marcos on 6/3/20.
//

#include "Server/ArgentumServerSide.h"
#include "TPException.h"
#include <iostream>
#include "Persistance/PlayerSaveFile.h"

int main(int argc, char** argv) {
    /*
    try {
        ArgentumServerSide::run(argc, argv);
    } catch (TPException& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Algo rompio bro" << std::endl;
    }
     */
    PlayerSaveFile saveFile("saveTestFile");
    PlayerData data;
    saveFile.storePlayerData(data, 0);
    return 0;
}
