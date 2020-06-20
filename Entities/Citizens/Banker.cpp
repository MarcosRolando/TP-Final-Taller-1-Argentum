//
// Created by agustin on 15/6/20.
//

#include "Banker.h"

class Player {
public:
    const std::string& getNickname() const;
    std::shared_ptr<Item> removeItem(const std::string& itemName);
};


Banker::Banker(Coordinate initialPosition): Entity(initialPosition) {

}


unsigned int Banker::list(const Player &player, std::list<ProductData> &products) {
    return playersStorages.at(player.getNickname()).getStorageData(products, 0);
}

void Banker::withdraw(Player &player, const std::string &itemName) {
    playersStorages.at(player.getNickname()).retreiveItem(itemName, player);

}

void Banker::deposit(Player &player, const std::string& itemName) {
    //storage.storeItem(player.removeItem(itemName));
    playersStorages.at(player.getNickname()).storeItem(player.removeItem(itemName));
}

void Banker::addPlayerItems(const std::string& playerName, const std::unordered_map<std::string, unsigned int>
                            &initialItemsAmounts, unsigned int gold) {
    playersStorages.emplace(playerName, Storage(initialItemsAmounts, gold));
}

