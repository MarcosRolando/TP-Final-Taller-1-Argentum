//
// Created by marcos on 6/28/20.
//

#include "PlayerManager.h"
#include "../Game/Game.h"
#include "PlayerData.hpp"
#include "../Entities/PlayerProxy.h"

PlayerProxy PlayerManager::addPlayer(PlayerData& playerData) {
    saveManager.storeNewPlayer(playerData);
    PlayerProxy player(&game, &game.createPlayer(playerData, protocol));
    return player;
}

PlayerData PlayerManager::getSavedPlayerData(const std::string &nickname) {
    return saveManager.getPlayerData(nickname);
}

