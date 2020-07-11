//
// Created by agustin on 15/6/20.
//

#include "Banker.h"

#include <memory>
#include "../Player.h"
#include "Storage.h"
#include "../../TPException.h"

#define MAX_NUMBER_OF_ITEMS_PER_PLAYER 20

std::unordered_map<std::string, Storage> Banker::playersStorages;

Banker::Banker(Coordinate initialPosition): Entity(GameType::BANKER,
                                                   initialPosition, "Banker") {

}

void Banker::list(Player &player) {
    playersStorages.at(player.getNickname()).second.getStorageData(player);
}


void Banker::withdraw(Player &player, const std::string &itemName) {
    try {
        std::pair<int32_t, Storage>& aux = playersStorages.at(player.getNickname());
        aux.second.retreiveItem(itemName, player);
    } catch (...) {
        throw TPException("Intentaron withdrawear un item de un player que no existia!");
    }
}

void Banker::deposit(Player &player, const std::string& itemName) {
    try {
        //AGREGAR UN OR POR SI SE RECIBE ORO, AHI NO IMPORTA CUANTOS ITEMS TIENE GUARDADOS
        std::pair<int32_t, Storage>& aux = playersStorages.at(player.getNickname());
        if (aux.first < MAX_NUMBER_OF_ITEMS_PER_PLAYER) {
            playersStorages.at(player.getNickname()).second.storeItem(player.removeItem(itemName));
            aux.first++;
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

////////////////////////////////////PRIVATE//////////////////////////////////////////

int32_t Banker::_getNumberOfItemsStored(const std::unordered_map<std::string, unsigned int> &
                                            initialItemsAmounts) {
    int32_t storedItemsAmmount = 0;
    for (const auto & itemList: initialItemsAmounts) {
        storedItemsAmmount += itemList.second;
    }
    return storedItemsAmmount;
}

