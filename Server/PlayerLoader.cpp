//
// Created by marcos on 6/28/20.
//

#include "PlayerLoader.h"
#include "../Game/Game.h"

PlayerProxy PlayerLoader::createPlayer(std::string&& nickname, GameType::Race race,
                                                GameType::Class _class) {
    PlayerProxy player(&game, &game.createPlayer(std::move(nickname), race, _class));
    return player;
}
