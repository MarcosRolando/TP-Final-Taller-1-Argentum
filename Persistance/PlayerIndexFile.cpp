//
// Created by marcos on 7/8/20.
//

#include "PlayerIndexFile.h"
#include <iostream>
#include <arpa/inet.h>
#include <vector>

PlayerIndexFile::PlayerIndexFile(const std::string& filePath) {
    indexFile.open(filePath, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
    if (!indexFile.is_open()) {
        std::cout << "No se encontro un archivo previo del indice con el nombre provisto."
                     " Se creo uno" << std::endl;
        std::ofstream newIndexFile(filePath);
        newIndexFile.close();
        indexFile.open(filePath, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
    } else {
        _loadFileDataToMap();
    }
}

void PlayerIndexFile::_loadFileDataToMap() {
    PlayerFilePosition offData{};
    uint32_t nicknameSize = 0;
    while (indexFile.peek() != std::fstream::traits_type::eof() || !indexFile.eof()) {
        indexFile.read(reinterpret_cast<char*>(&nicknameSize), sizeof(nicknameSize));
        nicknameSize = ntohl(nicknameSize);
        std::vector<char> playerNickname(nicknameSize);
        indexFile.read(playerNickname.data(), nicknameSize);
        indexFile.read(reinterpret_cast<char*>(&offData.offset), sizeof(offData.offset));
        indexFile.read(reinterpret_cast<char*>(&offData.length), sizeof(offData.length));
        offData.offset = ntohl(offData.offset);
        offData.length = ntohl(offData.length);
        players.emplace(playerNickname.data(), offData);
    }
}

void PlayerIndexFile::storeNewPlayer(std::string& playerNickname, PlayerFilePosition offData) {
    if (indexFile.eof()) indexFile.clear();
    offData = {htonl(offData.offset), htonl(offData.length)};
    uint32_t nameLength = playerNickname.size() + 1;
    nameLength = htonl(nameLength);
    indexFile.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
    indexFile.write(playerNickname.data(), playerNickname.size() + 1);
    indexFile.write(reinterpret_cast<char*>(&offData.offset), sizeof(offData.offset));
    indexFile.write(reinterpret_cast<char*>(&offData.length), sizeof(offData.length));
    players.emplace(playerNickname, offData);
}

void PlayerIndexFile::storeNewPlayer(std::string&& playerNickname, PlayerFilePosition offData) {
    storeNewPlayer(playerNickname, offData);
}
