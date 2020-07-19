//
// Created by marcos on 6/28/20.
//

#ifndef ARGENTUM_PLAYERMANAGER_H
#define ARGENTUM_PLAYERMANAGER_H

#include <string>
#include "../../libs/GameEnums.h"
#include "../Persistance/SaveFileManager.h"

class Game;
class PlayerProxy;
class ServerProtocol;
struct PlayerData;

class PlayerManager {
private:
    Game& game;
    ServerProtocol& protocol;
    SaveFileManager saveManager;

public:
    PlayerManager(Game& _game, ServerProtocol& _protocol,
                            const std::string& indexPath,
                            const std::string& savePath) : game(_game),
                            protocol(_protocol), saveManager(indexPath, savePath) {}

    PlayerProxy addPlayer(PlayerData& playerData);
    PlayerData getSavedPlayerData(const std::string& nickname);
    void storeNewPlayer(const PlayerData& playerData);
    void storeOldPlayer(const PlayerData& playerData);
    void removePlayer(const std::string& nickname);
};


#endif //ARGENTUM_PLAYERMANAGER_H
