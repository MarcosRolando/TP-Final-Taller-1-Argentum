//
// Created by ivan on 24/6/20.
//

#ifndef ARGENTUM_CLIENTPROTOCOL_H
#define ARGENTUM_CLIENTPROTOCOL_H

#include "../Shared/GameEnums.h"
#include <vector>
#include <msgpack/v1/object.hpp>

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
    void _processAddEntity(msgpack::object_handle &handler, std::size_t& offset);
    void _processAddItem(msgpack::object_handle &handler, std::size_t& offset);
};


#endif //ARGENTUM_CLIENTPROTOCOL_H
