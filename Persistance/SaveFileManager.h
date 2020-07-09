//
// Created by marcos on 9/7/20.
//

#ifndef ARGENTUM_SAVEFILEMANAGER_H
#define ARGENTUM_SAVEFILEMANAGER_H

#include "PlayerIndexFile.h"
#include "PlayerSaveFile.h"

class SaveFileManager {
private:
    PlayerIndexFile indexFile;
    PlayerSaveFile saveFile;

public:
    SaveFileManager(const std::string& indexPath, const std::string& savePath) :
                    indexFile(indexPath), saveFile(savePath) {}

    PlayerData getPlayerData(const std::string& playerNickname);
    void storeOldPlayer(const PlayerData& data);
    void storeNewPlayer(const PlayerData& data);
};


#endif //ARGENTUM_SAVEFILEMANAGER_H
