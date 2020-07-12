//
// Created by agustin on 15/6/20.
//

#include "Banker.h"

#include <memory>
#include "../Player.h"
#include "Storage.h"
#include "../../TPException.h"
#include "../../Config/Configuration.h"

#define MAX_NUMBER_OF_ITEMS_PER_PLAYER 20
#define NO_ROOM_AVAILABLE_MESSAGE "You don't have more storage room, the limit is "
#define ROOM_AVAILABLE_MESSAGE "Items stored: "
#define INVALID_GOLD_PARAMETERS "Invalid parameters for gold deposit/withdrawal\n"
#define INSUFFICIENT_GOLD_MESSAGE "Insufficient gold\n"
#define GOLD_AMMOUNT_SEPARATOR ' '

std::unordered_map<std::string, std::pair<unsigned int, Storage>> Banker::playersStorages;

Banker::Banker(Coordinate initialPosition): Entity(GameType::BANKER,
                                                   initialPosition, "Banker") {

}

void Banker::list(Player &player) {
    const std::pair<unsigned int, Storage>& aux = playersStorages.at(player.getNickname());
    aux.second.getStorageData(player);
    _storeAvailableRoomMessage(player, aux.first);
}


void Banker::withdraw(Player &player, const std::string &itemName) {
    try {
        std::pair<unsigned int, Storage>& aux = playersStorages.at(player.getNickname());
        if (aux.second.retreiveItem(itemName, player)) {
            aux.first--;
            _storeAvailableRoomMessage(player, aux.first);
        }
    } catch (...) {
        throw TPException("Intentaron withdrawear un item de un player que no existia!");
    }
}

void Banker::deposit(Player &player, const std::string& itemName) {
    try {
        std::pair<unsigned int, Storage>& aux = playersStorages.at(player.getNickname());
        if (itemName.find(Configuration::getInstance().configGetGoldName()) != std::string::npos) {
            _depositGold(aux, player, itemName);
        } else if ((aux.first < MAX_NUMBER_OF_ITEMS_PER_PLAYER) &&
                        (playersStorages.at(player.getNickname()).second.storeItem(player.removeItem(itemName)))) {
            aux.first++;
            _storeAvailableRoomMessage(player, aux.first);
        } else {
            player.addMessage(NO_ROOM_AVAILABLE_MESSAGE + std::to_string(MAX_NUMBER_OF_ITEMS_PER_PLAYER) + "\n");
        }
    } catch(...) {
        throw TPException("Intentaron depositar un item de un player que no existia!");
    }
}

/*
void Banker::addPlayerItems(const std::string& playerName, const std::unordered_map<std::string, unsigned int>
                            &initialItemsAmounts, unsigned int gold) {
    playersStorages.emplace(playerName, std::pair<int32_t, Storage>
                    (_getNumberOfItemsStored(initialItemsAmounts), Storage(initialItemsAmounts, gold)));
}
*/

void Banker::getPlayerItems(PlayerData &playerData) {
    auto & playerStorageData = playersStorages.at(playerData.nickname);
    playerStorageData.second.getPlayerData(playerData);
}

void Banker::addPlayerItems(const PlayerData &playerData) {
    std::unordered_map<std::string, unsigned int> initialItemsAmounts;
    unsigned int itemAmount = 0;
    std::tuple<GameType::ItemType, int32_t> currItemType = playerData.bankerItems.at(0);
    for (auto & item : playerData.bankerItems) {
        if (currItemType != item) {
            std::string itemName = _translateItemTypeToName(currItemType);
            initialItemsAmounts.emplace(itemName, itemAmount);
            itemAmount = 0;
            currItemType = item;
        } else {
            ++itemAmount;
        }
    }
    unsigned int gold = playerData.bankerGold;
    playersStorages.emplace(playerData.nickname, std::pair<int32_t, Storage>
            (_getNumberOfItemsStored(initialItemsAmounts), Storage(initialItemsAmounts, gold)));
}


void Banker::erasePlayerItems(const PlayerData &playerData) {

}


////////////////////////////////////PRIVATE//////////////////////////////////////////

int32_t Banker::_getNumberOfItemsStored(const std::unordered_map<std::string, unsigned int> &
                                            initialItemsAmounts) {
    int32_t storedItemsAmmount = 0;
    for (const auto & itemList: initialItemsAmounts) {
        storedItemsAmmount += itemList.second;
    }
    return storedItemsAmmount;
}

void Banker::_storeAvailableRoomMessage(Player &player, unsigned int storedItemsAmmount) {
    player.addMessage(ROOM_AVAILABLE_MESSAGE + std::to_string(storedItemsAmmount) + "/"
                      + std::to_string(MAX_NUMBER_OF_ITEMS_PER_PLAYER) + "\n");
}

void Banker::_depositGold(std::pair<unsigned int, Storage>& playerStorage, Player &player, const std::string& itemName) {
    int goldAmmount = 0;
    size_t separatorPosition = itemName.find(GOLD_AMMOUNT_SEPARATOR);
    if ((separatorPosition != std::string::npos) &&
        (separatorPosition != itemName.size() - 1)) {
        try {
            goldAmmount = std::stoi(itemName.substr(separatorPosition + 1));
            if (player.spendGold(goldAmmount)) {
                playerStorage.second.increaseGoldReserves(goldAmmount);
            } else {
                player.addMessage(INSUFFICIENT_GOLD_MESSAGE);
            }
        } catch (std::invalid_argument &e) {
            player.addMessage(INVALID_GOLD_PARAMETERS);
        } catch (std::out_of_range &e) {
            player.addMessage(INVALID_GOLD_PARAMETERS);
        }
    } else {
        player.addMessage(INVALID_GOLD_PARAMETERS);
    }
}

std::string Banker::_translateItemTypeToName(std::tuple<GameType::ItemType, int32_t> item) {
    Configuration& config = Configuration::getInstance();
    switch (std::get<0>(item)) {
        case GameType::ITEM_TYPE_CLOTHING:
            return config.configClothingData(
                    static_cast<GameType::Clothing>(std::get<1>(item))).name;
        case GameType::ITEM_TYPE_WEAPON:
            return config.configWeaponData(
                    static_cast<GameType::Weapon>(std::get<1>(item))).name;
        case GameType::ITEM_TYPE_POTION:
            return config.configPotionData(
                    static_cast<GameType::Potion>(std::get<1>(item))).name;
        default:
            //do nothing
            throw TPException("El jugador guardaba items de banker invalidos!");
    }
}

