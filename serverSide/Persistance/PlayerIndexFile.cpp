//
// Created by marcos on 7/8/20.
//

#include "PlayerIndexFile.h"
#include <iostream>
#include <arpa/inet.h>
#include <vector>
#include "../../libs/TPException.h"
#include "../Exceptions/InexistentPlayerException.h"

PlayerIndexFile::PlayerIndexFile(const std::string& filePath) {
    indexFile.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
    if (!indexFile.is_open()) {
        std::cout << "No se encontro un archivo previo del indice con el nombre provisto."
                     " Se creo uno" << std::endl;
        std::ofstream newIndexFile(filePath);
        newIndexFile.close();
        indexFile.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
    } else {
        _loadFileData();
    }
}

void PlayerIndexFile::_loadFileData() {
    PlayerFilePosition offData{};
    uint32_t nicknameSize = 0;
    indexFile.seekg(0, std::ios_base::beg);
    while (indexFile.peek() != std::fstream::traits_type::eof() || !indexFile.eof()) {
        indexFile.read(reinterpret_cast<char*>(&nicknameSize), sizeof(nicknameSize));
        nicknameSize = ntohl(nicknameSize);
        std::vector<char> playerNickname(nicknameSize);
        indexFile.read(playerNickname.data(), nicknameSize);
        indexFile.read(reinterpret_cast<char*>(&offData.offset), sizeof(offData.offset));
        indexPlayersPosition.emplace(playerNickname.data(), indexFile.tellg());
        indexFile.read(reinterpret_cast<char*>(&offData.length), sizeof(offData.length));
        offData.offset = ntohl(offData.offset);
        offData.length = ntohl(offData.length);
        players.emplace(playerNickname.data(), offData);
    }
}

void PlayerIndexFile::storeOldPlayer(const std::string& playerNickname, PlayerFilePosition filePosition) {
    indexFile.clear();
    filePosition = {htonl(filePosition.offset), htonl(filePosition.length)};
    if (players.count(playerNickname) == 1) {
        indexFile.seekp(indexPlayersPosition.at(playerNickname), std::ios_base::beg);
        indexFile.write(reinterpret_cast<char*>(&filePosition.length), sizeof(filePosition.length));
        indexFile.sync();
    } else {
        throw TPException("Intentaron guardar un player viejo que no existia!");
    }
}

PlayerFilePosition PlayerIndexFile::getPlayerPosition(const std::string& nickname) {
    if (playerExists(nickname)) {
        return players.at(nickname);
    }
    throw InexistentPlayerException();
}

void PlayerIndexFile::storeNewPlayer(const std::string &playerNickname,
                                     PlayerFilePosition filePosition) {

    players.emplace(playerNickname, filePosition);
    indexFile.clear();
    indexFile.seekp(0, std::ios_base::end);
    filePosition = {htonl(filePosition.offset), htonl(filePosition.length)};
    uint32_t nameLength = playerNickname.size() + 1;
    nameLength = htonl(nameLength);
    indexFile.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
    indexFile.write(playerNickname.data(), playerNickname.size() + 1);
    indexFile.write(reinterpret_cast<char*>(&filePosition.offset), sizeof(filePosition.offset));
    indexPlayersPosition.emplace(playerNickname, indexFile.tellp());
    indexFile.write(reinterpret_cast<char*>(&filePosition.length), sizeof(filePosition.length));
    indexFile.sync();
}

bool PlayerIndexFile::playerExists(const std::string& nickname) const {
    return (players.count(nickname) == 1);
}
