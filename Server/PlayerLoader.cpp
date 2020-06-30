//
// Created by marcos on 6/28/20.
//

#include "PlayerLoader.h"
#include "../Game/Game.h"
#include "../Entities/PlayerProxy.h"

PlayerProxy PlayerLoader::getPlayer(/*recibimos el nickname*/) {
    //todo conseguir lo sdatos del player del archivo
    PlayerProxy player(&game, &game.loadPlayer(/*todo pasarle un struct con los datos del player o algo*/));
    return player;
}
