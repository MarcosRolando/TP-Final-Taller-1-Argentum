//
// Created by marcos on 6/28/20.
//

#ifndef ARGENTUM_PLAYERLOADER_H
#define ARGENTUM_PLAYERLOADER_H

#include <string>
#include "../Config/GameEnums.h"

class Game;
class PlayerProxy;

class PlayerLoader {
private:
    Game& game;

public:
    explicit PlayerLoader(Game& _game) : game(_game) {}
    PlayerProxy createPlayer(std::string&& nickname, GameType::Race race,
                                        GameType::Class _class);
};


#endif //ARGENTUM_PLAYERLOADER_H
