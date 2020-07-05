//
// Created by marcos on 6/28/20.
//

#ifndef ARGENTUM_PLAYERLOADER_H
#define ARGENTUM_PLAYERLOADER_H

#include <string>
#include "../Config/GameEnums.h"

class Game;
class PlayerProxy;
class ServerProtocol;
struct InitialPlayerData;

class PlayerLoader {
private:
    Game& game;
    ServerProtocol& protocol;

public:
    explicit PlayerLoader(Game& _game, ServerProtocol& _protocol) : game(_game),
                                                        protocol(_protocol) {}
    PlayerProxy createPlayer(InitialPlayerData& playerData);
};


#endif //ARGENTUM_PLAYERLOADER_H
