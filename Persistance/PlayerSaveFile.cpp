//
// Created by marcos on 7/8/20.
//

#include "PlayerSaveFile.h"
#include <iostream>
#include <msgpack.hpp>

MSGPACK_ADD_ENUM(GameType::Race)
MSGPACK_ADD_ENUM(GameType::Class)
MSGPACK_ADD_ENUM(GameType::ItemType)
MSGPACK_ADD_ENUM(GameType::EquipmentPlace)

PlayerSaveFile::PlayerSaveFile(const std::string &filePath) {
    saveFile.open(filePath, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
    if (!saveFile.is_open()) {
        std::cout << "No se encontro un archivo previo de jugadores con el nombre provisto."
                     " Se creo uno" << std::endl;
        std::ofstream newSaveFile(filePath);
        newSaveFile.close();
        saveFile.open(filePath, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
    }
}

void PlayerSaveFile::getPlayerData(const std::string& playerNickname) {

}

PlayerFilePosition PlayerSaveFile::storePlayerData(const PlayerData& playerData,
                                            int32_t fileOffset) {
    if (saveFile.eof()) saveFile.clear();
    PlayerFilePosition playerPosition{};
    playerPosition.offset = fileOffset;
    std::stringstream dataToStore;
    _packPlayerType(dataToStore, playerData);
    _packPlayerGeneralStats(dataToStore, playerData);
    _packPlayerInventory(dataToStore, playerData);
    //todo agregar los items que guarda el banker
    std::string strDataToStore = dataToStore.str();
    playerPosition.length = strDataToStore.length();
    saveFile.seekp(fileOffset, std::ios_base::beg);
    saveFile.write(strDataToStore.data(), playerPosition.length);
    //todo agregar padding
    return playerPosition;
}

void PlayerSaveFile::_packPlayerType(std::stringstream& dataToStore,
                                            const PlayerData& playerData) {
    msgpack::type::tuple<std::string, GameType::Race, GameType::Class> playerType(
                        playerData.nickname, playerData.pRace, playerData.pClass);
    msgpack::pack(dataToStore, playerType);
}

void PlayerSaveFile::_packPlayerGeneralStats(std::stringstream& dataToStore,
                                            const PlayerData& playerData) {
    msgpack::type::tuple<int32_t, int32_t, int32_t> generalStats(playerData.level,
                                        playerData.experience, playerData.gold);
    msgpack::pack(dataToStore, generalStats);
    msgpack::type::tuple<int32_t, int32_t, int32_t, int32_t> stats(playerData.constitution,
                                playerData.strength, playerData.agility, playerData.intelligence);
    msgpack::pack(dataToStore, stats);
}

void PlayerSaveFile::_packPlayerInventory(std::stringstream& dataToStore,
                                          const PlayerData& playerData) {
    for (auto & currItem : playerData.inventory) {
        msgpack::type::tuple<GameType::ItemType, int32_t> item(currItem);
        msgpack::pack(dataToStore, item);
    }
    for (auto & currItem : playerData.equipment) {
        msgpack::type::tuple<GameType::EquipmentPlace, int32_t> item(currItem);
        msgpack::pack(dataToStore, item);
    }
}
