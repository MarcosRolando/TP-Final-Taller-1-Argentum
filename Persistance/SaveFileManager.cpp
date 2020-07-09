//
// Created by marcos on 9/7/20.
//

#include "SaveFileManager.h"

PlayerData SaveFileManager::getPlayerData(const std::string &playerNickname) {
    std::lock_guard<std::mutex> l(m);
    PlayerFilePosition filePosition = indexFile.getPlayerPosition(playerNickname);
    return saveFile.getPlayerData(playerNickname, filePosition);
}

void SaveFileManager::storeNewPlayer(const PlayerData &data) {
    std::lock_guard<std::mutex> l(m);
    PlayerFilePosition filePosition = saveFile.storePlayerData(data);
    indexFile.storeNewPlayer(data.nickname, filePosition);
}

void SaveFileManager::storeOldPlayer(const PlayerData &data) {
    std::lock_guard<std::mutex> l(m);
    PlayerFilePosition filePosition = indexFile.getPlayerPosition(data.nickname);
    filePosition = saveFile.storePlayerData(data, filePosition.offset);
    indexFile.storeOldPlayer(data.nickname, filePosition);
}
