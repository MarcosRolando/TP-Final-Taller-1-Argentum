//
// Created by agustin on 15/6/20.
//

#include "Banker.h"

#include <memory>
#include "../Player.h"
#include "Storage.h"
#include "../../TPException.h"

#define MAX_NUMBER_OF_ITEMS_PER_PLAYER 20
#define NO_ROOM_AVAILABLE_MESSAGE "You don't have more storage room, the limit is "
#define ROOM_AVAILABLE_MESSAGE "Items stored: "

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
        //AGREGAR UN OR POR SI SE RECIBE ORO, AHI NO IMPORTA CUANTOS ITEMS TIENE GUARDADOS
        std::pair<unsigned int, Storage>& aux = playersStorages.at(player.getNickname());
        if ((aux.first < MAX_NUMBER_OF_ITEMS_PER_PLAYER) &&
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

void Banker::addPlayerItems(const std::string& playerName, const std::unordered_map<std::string, unsigned int>
                            &initialItemsAmounts, unsigned int gold) {
    playersStorages.emplace(playerName, std::pair<int32_t, Storage>
                    (_getNumberOfItemsStored(initialItemsAmounts), Storage(initialItemsAmounts, gold)));
}

void Banker::getPlayerItems(PlayerData &playerData) {
    auto & playerStorageData = playersStorages.at(playerData.nickname);
    playerStorageData.second.getPlayerData(playerData);
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

