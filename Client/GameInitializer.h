//
// Created by marcos on 7/1/20.
//

#ifndef ARGENTUM_GAMEINITIALIZER_H
#define ARGENTUM_GAMEINITIALIZER_H

#include <vector>
#include <string>
#include "../Shared/GameEnums.h"

class GameGUI;
class Socket;
class ClientProtocol;

class GameInitializer {
private:
    GameGUI& game;
    Socket& socket;
    ClientProtocol& protocol;

public:
    GameInitializer(GameGUI& _game, Socket& _socket, ClientProtocol& _protocol) :
                    game(_game), socket(_socket), protocol(_protocol) {}
    void loadPlayer(const std::string &nickname, GameType::Race race,
                       GameType::Class _class);
    void loadPlayer(std::string &nickname);
    void initializeGame();

private:
    void _receiveMapInfo();
    void _receiveCurrentGameState();
    void _loadMap(std::vector<char>& buffer);
    void _processAddEntity(std::vector<char>& buffer, std::size_t& offset);
};


#endif //ARGENTUM_GAMEINITIALIZER_H
