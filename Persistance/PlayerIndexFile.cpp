//
// Created by marcos on 7/8/20.
//

#include "PlayerIndexFile.h"
#include <iostream>
#include <arpa/inet.h>
#include <vector>
#include "../TPException.h"

PlayerIndexFile::PlayerIndexFile(const std::string& filePath) {
    indexFile.open(filePath, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
    if (!indexFile.is_open()) {
        std::cout << "No se encontro un archivo previo del indice con el nombre provisto."
                     " Se creo uno" << std::endl;
        std::ofstream newIndexFile(filePath);
        newIndexFile.close();
        indexFile.open(filePath, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
    } else {
        _loadFileData();
    }
}

void PlayerIndexFile::_loadFileData() {
    PlayerFilePosition offData{};
    uint32_t nicknameSize = 0;
    int32_t readPlayers = 0;
    while (indexFile.peek() != std::fstream::traits_type::eof() || !indexFile.eof()) {
        indexFile.read(reinterpret_cast<char*>(&nicknameSize), sizeof(nicknameSize));
        nicknameSize = ntohl(nicknameSize);
        std::vector<char> playerNickname(nicknameSize);
        indexFile.read(playerNickname.data(), nicknameSize);
        indexFile.read(reinterpret_cast<char*>(&offData.offset), sizeof(offData.offset));
        readPlayers = indexFile.tellg();
        indexFile.read(reinterpret_cast<char*>(&offData.length), sizeof(offData.length));
        offData.offset = ntohl(offData.offset);
        offData.length = ntohl(offData.length);
        players.emplace(playerNickname.data(), offData);
        indexPlayersPosition.emplace(playerNickname.data(), readPlayers);
    }
}

void PlayerIndexFile::storePlayer(const std::string& playerNickname, PlayerFilePosition filePosition) {
    indexFile.clear();
    filePosition = {htonl(filePosition.offset), htonl(filePosition.length)};
    if (players.count(playerNickname) == 1) {
        indexFile.seekp(indexPlayersPosition.at(playerNickname), std::ios_base::beg);
        indexFile.write(reinterpret_cast<char*>(&filePosition.length), sizeof(filePosition.length));
    } else {
        throw TPException("Intentaron guardar un player en el indice que no esta creado!");
    }
}

PlayerFilePosition PlayerIndexFile::getPlayerPosition(const std::string& nickname) {
    if (players.count(nickname) == 0) {
        _storeNewPlayer(nickname);
    }
    return players.at(nickname);

}

void PlayerIndexFile::_storeNewPlayer(const std::string& nickname) {
    indexFile.clear();
    indexFile.seekp(std::ios_base::end);

    uint32_t nameLength = nickname.size() + 1;
    nameLength = htonl(nameLength);
    indexFile.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
    indexFile.write(nickname.data(), nickname.size() + 1);
    indexFile.write(reinterpret_cast<char*>(&nickname.offset), sizeof(filePosition.offset));
    indexPlayersPosition.emplace(nickname, indexFile.tellp());
    indexFile.write(reinterpret_cast<char*>(&filePosition.length), sizeof(filePosition.length));
    players.emplace(nickname, filePosition);
}
