//
// Created by marcos on 9/7/20.
//

#include "SaveFileManager.h"
#include "../Exceptions/UnavailablePlayerException.h"

PlayerData SaveFileManager::getPlayerData(const std::string &playerNickname) {
    std::lock_guard<std::mutex> l(m);
    PlayerFilePosition filePosition = indexFile.getPlayerPosition(playerNickname);
    return saveFile.getPlayerData(playerNickname, filePosition);
}

void SaveFileManager::storeNewPlayer(const PlayerData &data) {
    std::lock_guard<std::mutex> l(m);
    if (indexFile.playerExists(data.nickname)) {
        throw UnavailablePlayerException();
    }
    PlayerFilePosition filePosition = saveFile.storePlayerData(data);
    indexFile.storeNewPlayer(data.nickname, filePosition);
}

void SaveFileManager::storeOldPlayer(const PlayerData &data) {
    std::lock_guard<std::mutex> l(m);
    PlayerFilePosition filePosition = indexFile.getPlayerPosition(data.nickname);
    filePosition = saveFile.storePlayerData(data, filePosition.offset);
    indexFile.storeOldPlayer(data.nickname, filePosition);
}
