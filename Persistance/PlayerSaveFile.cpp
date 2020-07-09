//
// Created by marcos on 7/8/20.
//

#include "PlayerSaveFile.h"
#include <iostream>
#include <msgpack.hpp>

PlayerSaveFile::PlayerSaveFile(const std::string &filePath) {
    saveFile.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
    if (!saveFile.is_open()) {
        std::cout << "No se encontro un archivo previo de jugadores con el nombre provisto."
                     " Se creo uno" << std::endl;
        std::ofstream newSaveFile(filePath);
        newSaveFile.close();
        saveFile.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
    }
}

void PlayerSaveFile::getPlayerData(const std::string& playerNickname) {

}

PlayerFilePosition PlayerSaveFile::storePlayerData(const PlayerData& playerData) {

}
