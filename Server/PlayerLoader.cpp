//
// Created by marcos on 6/28/20.
//

#include "PlayerLoader.h"
#include "../Game/Game.h"
#include "PlayerData.h"
#include "../Entities/PlayerProxy.h"

PlayerProxy PlayerLoader::createPlayer(PlayerData& playerData) {
    PlayerProxy player(&game, &game.createPlayer(playerData, protocol));
    return player;
}
