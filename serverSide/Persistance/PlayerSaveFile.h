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

    /*Retorna la data guardada del player (stats, inventario, banker items, etc)*/
    PlayerData getPlayerData(const std::string& playerNickname,
                             PlayerFilePosition filePosition);

    /*Almacena la informacion del player provisto en la posicion especificada
     * en el offset*/
    PlayerFilePosition storePlayerData(const PlayerData& playerData,
                                       int32_t fileOffset);

    /*Sobrecarga para storePlayerData, esta funcion se usa para almacenar un nuevo
     * player en el archivo (no recibe offset porque siempre ira al final del archivo*/
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
