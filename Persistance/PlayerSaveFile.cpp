//
// Created by marcos on 7/8/20.
//

#include "PlayerSaveFile.h"
#include <iostream>
#include "../TPException.h"

MSGPACK_ADD_ENUM(GameType::Race)
MSGPACK_ADD_ENUM(GameType::Class)
MSGPACK_ADD_ENUM(GameType::ItemType)
MSGPACK_ADD_ENUM(GameType::EquipmentPlace)

PlayerSaveFile::PlayerSaveFile(const std::string &filePath) {
    saveFile.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
    if (!saveFile.is_open()) {
        std::cout << "No se encontro un archivo previo de jugadores con el nombre provisto."
                     " Se creo uno" << std::endl;
        std::ofstream newSaveFile(filePath);
        newSaveFile.close();
        saveFile.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
    }
}

PlayerData PlayerSaveFile::getPlayerData(const std::string& playerNickname,
                                        PlayerFilePosition filePosition) {
    saveFile.clear();
    saveFile.seekg(filePosition.offset, std::ios_base::beg);
    readData = 0;
    std::vector<char> playerDataBuffer(filePosition.length);
    saveFile.read(playerDataBuffer.data(), filePosition.length);
    PlayerData playerData;
    _loadPlayerType(playerData, playerDataBuffer);
    if (playerData.nickname != playerNickname) {
        throw TPException("El nombre del jugador almacenado no coincide con "
                          "el esperado!");
    }
    _loadPlayerGeneralStats(playerData, playerDataBuffer);
    _loadPlayerInventory(playerData, playerDataBuffer);
    _loadPlayerBank(playerData, playerDataBuffer);
    return playerData;
}

void PlayerSaveFile::_loadPlayerBank(PlayerData& playerData,
                                          std::vector<char>& playerDataBuffer) {

    for (auto & currItem : playerData.bankerItems) {
        msgpack::type::tuple<GameType::ItemType, int32_t> item;
        handler = msgpack::unpack(playerDataBuffer.data(), playerData.size(), readData);
        handler->convert(item);
        currItem = item;
    }
    msgpack::type::tuple<int32_t> bankGold;
    handler = msgpack::unpack(playerDataBuffer.data(), playerData.size(), readData);
    handler->convert(bankGold);
    playerData.bankerGold = std::get<0>(bankGold);
}

void PlayerSaveFile::_loadPlayerInventory(PlayerData& playerData,
                                             std::vector<char>& playerDataBuffer) {

    for (auto & currItem : playerData.inventory) {
        msgpack::type::tuple<GameType::ItemType, int32_t> item;
        handler = msgpack::unpack(playerDataBuffer.data(), playerData.size(), readData);
        handler->convert(item);
        currItem = item;
    }
    msgpack::type::tuple<int32_t> equipment;
    handler = msgpack::unpack(playerDataBuffer.data(), playerData.size(), readData);
    handler->convert(equipment);
    playerData.equipment.at(GameType::EQUIPMENT_PLACE_HEAD) = std::get<0>(equipment);
    handler = msgpack::unpack(playerDataBuffer.data(), playerData.size(), readData);
    handler->convert(equipment);
    playerData.equipment.at(GameType::EQUIPMENT_PLACE_CHEST) = std::get<0>(equipment);
    handler = msgpack::unpack(playerDataBuffer.data(), playerData.size(), readData);
    handler->convert(equipment);
    playerData.equipment.at(GameType::EQUIPMENT_PLACE_SHIELD) = std::get<0>(equipment);
    handler = msgpack::unpack(playerDataBuffer.data(), playerData.size(), readData);
    handler->convert(equipment);
    playerData.equipment.at(GameType::EQUIPMENT_PLACE_WEAPON) = std::get<0>(equipment);
}

void PlayerSaveFile::_loadPlayerGeneralStats(PlayerData& playerData,
                                     std::vector<char>& playerDataBuffer) {
    msgpack::type::tuple<int32_t, int32_t, int32_t> generalStats;
    handler = msgpack::unpack(playerDataBuffer.data(), playerData.size(), readData);
    handler->convert(generalStats);
    playerData.level = std::get<0>(generalStats);
    playerData.experience = std::get<1>(generalStats);
    playerData.gold = std::get<2>(generalStats);
    msgpack::type::tuple<int32_t, int32_t, int32_t, int32_t> stats;
    handler = msgpack::unpack(playerDataBuffer.data(), playerData.size(), readData);
    handler->convert(stats);
    playerData.constitution = std::get<0>(stats);
    playerData.strength = std::get<1>(stats);
    playerData.agility = std::get<2>(stats);
    playerData.intelligence = std::get<3>(stats);
}

void PlayerSaveFile::_loadPlayerType(PlayerData& playerData,
                                        std::vector<char>& playerDataBuffer) {
    msgpack::type::tuple<std::string, GameType::Race, GameType::Class> playerType;
    handler = msgpack::unpack(playerDataBuffer.data(), playerData.size(), readData);
    handler->convert(playerType);
    playerData.nickname = std::move(std::get<0>(playerType));
    playerData.pRace = std::get<1>(playerType);
    playerData.pClass = std::get<2>(playerType);
}

PlayerFilePosition PlayerSaveFile::storePlayerData(const PlayerData& playerData,
                                            int32_t fileOffset) {
    saveFile.clear();
    saveFile.seekp(fileOffset, std::ios_base::beg);
    PlayerFilePosition playerPosition{};
    playerPosition.offset = fileOffset;
    std::stringstream dataToStore;
    _packPlayerType(dataToStore, playerData);
    _packPlayerGeneralStats(dataToStore, playerData);
    _packPlayerInventory(dataToStore, playerData);
    _packBankItems(dataToStore, playerData);
    std::string strDataToStore = dataToStore.str();
    playerPosition.length = strDataToStore.length();
    saveFile.seekp(fileOffset, std::ios_base::beg);
    saveFile.write(strDataToStore.data(), playerPosition.length);
    int32_t paddingSize = (playerData.size() - playerPosition.length);
    std::vector<char> paddingBuffer(paddingSize, 0);
    saveFile.write(paddingBuffer.data(), paddingSize);
    saveFile.sync();
    return playerPosition;
}

void PlayerSaveFile::_packBankItems(std::stringstream& dataToStore,
                                    const PlayerData& playerData) {
    for (auto & currItem : playerData.bankerItems) {
        msgpack::type::tuple<GameType::ItemType, int32_t> item(currItem);
        msgpack::pack(dataToStore, item);
    }
    msgpack::type::tuple<int32_t> gold(playerData.bankerGold);
    msgpack::pack(dataToStore, gold);
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
    msgpack::type::tuple<int32_t> helmet(playerData.equipment.at(GameType::EQUIPMENT_PLACE_HEAD));
    msgpack::pack(dataToStore, helmet);
    msgpack::type::tuple<int32_t> chest(playerData.equipment.at(GameType::EQUIPMENT_PLACE_CHEST));
    msgpack::pack(dataToStore, chest);
    msgpack::type::tuple<int32_t> shield(playerData.equipment.at(GameType::EQUIPMENT_PLACE_SHIELD));
    msgpack::pack(dataToStore, shield);
    msgpack::type::tuple<int32_t> weapon(playerData.equipment.at(GameType::EQUIPMENT_PLACE_WEAPON));
    msgpack::pack(dataToStore, weapon);
}

PlayerFilePosition PlayerSaveFile::storePlayerData(const PlayerData &playerData) {
    saveFile.seekp(0, std::ios_base::end);
    return storePlayerData(playerData, saveFile.tellp());
}
