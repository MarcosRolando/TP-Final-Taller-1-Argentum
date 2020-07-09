//
// Created by marcos on 7/8/20.
//

#ifndef ARGENTUM_PLAYERSAVEFILE_H
#define ARGENTUM_PLAYERSAVEFILE_H

#include <fstream>
#include "PlayerFilePosition.h"
#include "../Server/PlayerData.hpp"

/*Esta clase es la que maneja el archivo que contiene los datos del player
 * guardado*/
class PlayerSaveFile {
private:
    std::fstream saveFile;

public:
    explicit PlayerSaveFile(const std::string& filePath);
    void getPlayerData(const std::string& playerNickname);
    PlayerFilePosition storePlayerData(const PlayerData& playerData,
                                       int32_t fileOffset);
private:
    static void _packPlayerType(std::stringstream& dataToStore, const PlayerData& playerData);
    static void _packPlayerGeneralStats(std::stringstream& dataToStore,
                                                 const PlayerData& playerData);
    static void _packPlayerInventory(std::stringstream& dataToStore,
                                              const PlayerData& playerData);
};


#endif //ARGENTUM_PLAYERSAVEFILE_H
