//
// Created by ivan on 24/6/20.
//

#ifndef ARGENTUM_CLIENTPROTOCOL_H
#define ARGENTUM_CLIENTPROTOCOL_H

#include "../Shared/GameEnums.h"
#include <vector>

class GameGUI;
class Socket;

class ClientProtocol {
private:
    GameGUI& game;
    Socket& socket;
    std::vector<char> buffer;

public:
    ClientProtocol(GameGUI& _game, Socket& _socket);

private:
    void _receiveMapInfo();
    void _loadMap();
    void _receiveCurrentGameState();
};


#endif //ARGENTUM_CLIENTPROTOCOL_H
