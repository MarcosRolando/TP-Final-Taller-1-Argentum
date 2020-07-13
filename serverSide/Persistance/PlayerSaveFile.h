//
// Created by marcos on 7/8/20.
//

#ifndef ARGENTUM_PLAYERSAVEFILE_H
#define ARGENTUM_PLAYERSAVEFILE_H

#include <fstream>
#include "PlayerFilePosition.h"
#include "../Server/PlayerData.hpp"
#include <vector>

/*Esta clase es la que maneja el archivo que contiene los datos del player
 * guardado*/
class PlayerSaveFile {
private:
    std::fstream saveFile;
    msgpack::object_handle handler;
    std::size_t readData{0};

public:
    explicit PlayerSaveFile(const std::string& filePath);
    PlayerData getPlayerData(const std::string& playerNickname,
                             PlayerFilePosition filePosition);
    PlayerFilePosition storePlayerData(const PlayerData& playerData,
                                       int32_t fileOffset);
    PlayerFilePosition storePlayerData(const PlayerData& playerData);

private:
    static void _packPlayerType(std::stringstream& dataToStore, const PlayerData& playerData);
    static void _packPlayerGeneralStats(std::stringstream& dataToStore,
                                                 const PlayerData& playerData);
    static void _packPlayerInventory(std::stringstream& dataToStore,
                                              const PlayerData& playerData);
    void _loadPlayerType(PlayerData& playerData,
                                         std::vector<char>& playerDataBuffer);
    void _loadPlayerGeneralStats(PlayerData& playerData,
                                                 std::vector<char>& playerDataBuffer);
    void _loadPlayerInventory(PlayerData& playerData, std::vector<char>& playerDataBuffer);
    static void _packBankItems(std::stringstream& dataToStore, const PlayerData& playerData);
    void _loadPlayerBank(PlayerData& playerData, std::vector<char>& playerDataBuffer);
};


#endif //ARGENTUM_PLAYERSAVEFILE_H
