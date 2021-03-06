//
// Created by marcos on 6/28/20.
//

#include "PlayerManager.h"
#include "../Game/Game.h"
#include "PlayerData.hpp"
#include "../Entities/PlayerProxy.h"
#include "../Exceptions/UnavailablePlayerException.h"

PlayerProxy PlayerManager::addPlayer(PlayerData& playerData) {
    PlayerProxy player(&game, &game.createPlayer(playerData, protocol));
    return player;
}

PlayerData PlayerManager::getSavedPlayerData(const std::string &nickname) {
    if (!game.playerExists(nickname)) {
        return saveManager.getPlayerData(nickname);
    }
    throw UnavailablePlayerException();
}

void PlayerManager::storeNewPlayer(PlayerData& playerData) {
    saveManager.storeNewPlayer(playerData);
}

void PlayerManager::storeOldPlayer(const PlayerData& playerData) {
    saveManager.storeOldPlayer(playerData);
}

void PlayerManager::removePlayer(const std::string &nickname) {
    game.removePlayer(nickname, protocol);
}

