//
// Created by marcos on 9/7/20.
//

#include "SaveFileManager.h"

PlayerData SaveFileManager::getPlayerData(const std::string &playerNickname) {
    PlayerFilePosition filePosition = indexFile.getPlayerPosition(playerNickname);
    return saveFile.getPlayerData(playerNickname, filePosition);
}

void SaveFileManager::storePlayerData(const PlayerData &data) {
    PlayerFilePosition filePosition = indexFile.getPlayerPosition(data.nickname);
    filePosition = saveFile.storePlayerData(data, filePosition.offset);
    indexFile.storePlayer(data.nickname, filePosition);
}
